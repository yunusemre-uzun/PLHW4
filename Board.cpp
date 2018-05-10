#include "Board.h"
#include "Coordinate.h"
#include "Entity.h"
#include <iostream>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Board::Board(uint boardSize, std::vector<Player *> *players): boardSize(boardSize), 
        hill(Coordinate(boardSize/2,boardSize/2)){
    std::vector<Player*> p;
    this->players = players; 
    this->stormwidth=0;
    this->stormdamage=0; 
}

Board::~Board(){
}

uint Board::getSize() const {
    return boardSize;
}

bool Board::isCoordInBoard(const Coordinate& coord) const {
    if(coord.x<0 || coord.y<0){
        return false;
    }
    else if(coord.x>boardSize-1 || coord.y>boardSize-1){
        return false;
    }
    else{
        return true;
    }
}

bool Board::isStormInCoord(const Coordinate &coord) const {
    if(stormwidth==0){
        return false;
    }
    else if(coord==hill){
        return false;
    }
    else{
        bool flag=0;
        for(int i=1;i<=stormwidth;i++){
            flag = flag || checkforRow(coord,i-1) || checkforRow(coord,boardSize-i);
        }
        for(int i=1;i<=stormwidth;i++){
            flag = flag || checkforColumn(coord,i-1) || checkforColumn(coord,boardSize-i);
        }
        return flag;
    }
    //std::cout << coord << std::endl;
}

bool Board::checkforRow(const Coordinate &coor,int i) const{
    bool flag = 0 ;
    for(int j=0;j<boardSize;j++){
        flag = flag || Coordinate(j,i)==coor;
    }
    return flag;
}

bool Board::checkforColumn(const Coordinate &coor,int i) const{
    bool flag = 0 ;
    for(int j=0;j<boardSize;j++){
        flag = flag || Coordinate(i,j)==coor;
    }
    return flag;
}

bool Board::isCoordHill(const Coordinate& coord) const{
    return coord==hill;
}

Player* Board::operator[](const Coordinate& coord) const{
    for(int i=0;i<players->size();i++){
        if((*players)[i]==nullptr){
            continue;
        }
        else{
            if((*players)[i]->getCoord()==coord){
                return (*players)[i] ;
            }
        }
    }
    return nullptr;
}

Coordinate Board::calculateCoordWithMove(Move move, const Coordinate &coord) const{
    Coordinate newcord = (coord)+move;
    if(!isCoordInBoard(newcord)){
        return coord;
    }
    else if((*this)[newcord] == nullptr){
        return newcord;
    }
    else{
        return coord;
    }
}

std::vector<Coordinate> Board::visibleCoordsFromCoord(const Coordinate &coord) const{
    std::vector<Coordinate> ret;
    if(isCoordInBoard(coord)){
        if(isCoordInBoard(Coordinate(coord.x-1,coord.y))){
            ret.push_back(Coordinate(coord.x-1,coord.y));
        }
        if(isCoordInBoard(Coordinate(coord.x+1,coord.y))){
            ret.push_back(Coordinate(coord.x+1,coord.y));
        }
        if(isCoordInBoard(Coordinate(coord.x,coord.y-1))){
            ret.push_back(Coordinate(coord.x,coord.y-1));
        }
        if(isCoordInBoard(Coordinate(coord.x,coord.y+1))){
            ret.push_back(Coordinate(coord.x,coord.y+1));
        }
    }
    return ret;
}
void Board::updateStorm(uint currentRound){
    stormwidth = Entity::stormWidthForRound(currentRound);
    stormdamage = Entity::stormDamageForRound(currentRound);
}