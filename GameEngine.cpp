#include "GameEngine.h"
#include <iostream>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/
GameEngine::GameEngine(uint boardSize, std::vector<Player *> *players)
                       :board(Board(boardSize,players)){
    currentRound = 1;
    this->players = players;
    numberofPlayers = players->size();
}

GameEngine::~GameEngine(){
    if(numberofPlayers==0){

    }
    else{
        for(int i=0;i<players->size();i++){
                if((*players)[i]==nullptr){
                    continue;
                }
                delete (*players)[i];
            }
    }
    players->clear();
    delete players;
}

const Board& GameEngine::getBoard() const{
    return this->board;
}

Player* GameEngine::operator[](uint id) const{
    for(int i=0;i<players->size();i++){
        if((*players)[i]->getID()==id){
            return (*players)[i];
        }
    }
    return nullptr;
}

bool GameEngine::isFinished() const{
    if(numberofPlayers==1){
        Player *p;
        for(int i=0;i<players->size();i++){
            if((*players)[i]){
                p= (*players)[i];
            }
        }
        if(board.isCoordHill(p->getCoord())){
            return true;
        }
        else{
            false;
        }
    }
    else if(numberofPlayers==0){
        return true;
    }
    else{
        return false;
    }
}

void GameEngine::takeTurn(){
    std::cout << "-- START ROUND " << currentRound << " --" << std::endl;
    board.updateStorm(currentRound);
    for(int i=0;i<players->size();i++){
        if((*players)[i]==nullptr)
            continue;
        takeTurnForPlayer((*players)[i]->getID());
    }
    std::cout << "-- END ROUND " << currentRound << " --" << std::endl;
    if(numberofPlayers==0){
        std::cout << "No one wins" << std::endl;
    }
    else if(numberofPlayers==1){
        Player *p;
        p = getWinnerPlayer();
        std::cout << p->getFullName() << " won!!!" <<std::endl;
    }
    currentRound++;
}

Move GameEngine::takeTurnForPlayer(uint playerID){
    Player *p;
    int i;
    for(i=0;i<players->size();i++){
        if((*players)[i]==nullptr)
            continue;
        if((*players)[i]->getID()==playerID){
            p = (*players)[i];
            break;
        }
    }
    if(p==nullptr){
        return NOOP;
    }
    else{
        std::vector<Move> plist = p->getPriorityList();
        std::vector<Coordinate> visibleCoords=board.visibleCoordsFromCoord(p->getCoord());
        bool isinStorm = board.isStormInCoord(p->getCoord());
        if(isinStorm){
            std::cout << p->getNamewithHP() << " is STORMED! (-" << board.getStormDamage() << ")" << std::endl;
            p->setHP(p->getHP()-board.getStormDamage());
        }
        if(p->isDead()){
            std::cout << p->getNamewithHP() << " DIED." << std::endl;
            std::cout << p->getFullName() << std::endl; 
            delete (*players)[i];
            (*players)[i]=nullptr;
            numberofPlayers--;
            return NOOP;
        }
        else{
            int i=0;
            for(;i<plist.size();i++){
                if(plist[i]==ATTACK){ /*attack */
                    std::vector<Player*> playersinrange = findPlayerInRange(visibleCoords);
                    if(playersinrange.size()>0){
                        Player *playerWithMinID = findPlayerWithMinID(p,playersinrange).first;
                        int min = findPlayerWithMinID(p,playersinrange).second;
                        p->attackTo(playerWithMinID);
                        if(playerWithMinID->isDead()){
                            int id = playerWithMinID->getID();
                            std::cout << playerWithMinID->getNamewithHP() << " DIED." << std::endl;
                            delete playerWithMinID;
                            (*players)[id]=nullptr;
                            numberofPlayers--;
                        }
                        return ATTACK;
                    }
                }
                else if(plist[i]==NOOP){
                    return NOOP;
                }
                else{
                    Coordinate t = board.calculateCoordWithMove(plist[i],p->getCoord());
                    if(t == p->getCoord()){
                        continue;
                    }
                    else{
                        if(t-board.getHillCoordinates()<p->getCoord()-board.getHillCoordinates()){
                            p -> executeMove(plist[i]);
                            return plist[i];
                        }
                        continue;
                    }
                }
            }
            return NOOP; 
        }
    }
}

std::vector<Player*> GameEngine::findPlayerInRange(std::vector<Coordinate> visiblecoords) const{
    int i,j;
    std::vector<Player*> ret;
    for(j=0;j<visiblecoords.size();j++){
        for(i=0;i<players->size();i++){
            if((*players)[i]==nullptr){
                continue;
            }
            else{
                if((*players)[i]->getCoord()==visiblecoords[j]){
                    ret.push_back((*players)[i]);
                }
            }
        }
    }
    return ret;
}

std::pair<Player*,int> GameEngine::findPlayerWithMinID(Player*p,std::vector<Player*> playersinrange) const{
    int i,min=1000,minID=1000;
    for(i=0;i<playersinrange.size();i++){
        if(playersinrange[i]==nullptr)
            continue;
        if(playersinrange[i]->getID()<minID && p->getID()!=playersinrange[i]->getID()){
            minID = playersinrange[i]->getID();
            min = i;
        }
    }
    //std::cout << playersinrange[min]->getFullName() << std::endl;
    std::pair<Player*,int> ret (playersinrange[min],min);
    return ret;
}

Player* GameEngine::getWinnerPlayer() const{
    if(numberofPlayers==0){
        return nullptr;
    }
    else{
        for(int i=0;i<players->size();i++){
            if((*players)[i]!=nullptr){
                return (*players)[i];
            }
        }
    }
}