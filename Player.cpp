#include "Player.h"
#include "Coordinate.h"
#include "Entity.h"
#include <string.h>
#include <iostream>

using namespace std;

Player::Player(uint idn, int x, int y) :id(idn),coordinate(Coordinate(x,y)){
    HP=100;
}
Player::~Player(){
    
}
uint Player::getID() const{
    return id;
}

const Coordinate& Player::getCoord() const{
    return coordinate;
}

int Player::getHP() const{
    return HP;
}

std::string Player::getBoardID() const{
    if(id>=10){
        return std::to_string(id);
    }
    else{
        std::string s = std::to_string(id);
        return "0"+s;
    }
    
}

bool Player::isDead() const {
    return (this->HP<=0);
}

void Player::executeMove(Move move){
    if(move==NOOP || move==ATTACK){
        return;
    }
    this -> coordinate = (this->coordinate)+move; // update the coordinate with given move
    //"-playerFullName(playerHP)- moved UP/DOWN/LEFT/RIGHT."
    cout << this->getNamewithHP() << " moved " ;
    switch(move){
        case UP:
            std::cout << "UP." << endl;
            break;
        case DOWN:
            std::cout << "DOWN." << endl;
            break;
        case LEFT:
            std::cout << "LEFT." << endl;
            break;
        case RIGHT:
            std::cout << "RIGHT." << endl;
            break;
    }
    return ;
}

bool Player::attackTo(Player *player){
    if(this==player){
        return false;
    }
    int currHP = player -> getHP();
    int damage = Entity::damageForWeapon(this -> getWeapon())-Entity::damageReductionForArmor(player->getArmor());
    if(damage){
        player -> setHP(currHP-damage);
        if(player->isDead()){
            cout << this->getNamewithHP() << " ATTACKED " << player->getFullName() << "("<<currHP<<")" << "! (-" << damage <<  ")" << endl; 
            return true;
        }
        else{
            cout << this->getNamewithHP() << " ATTACKED " << player->getFullName() << "("<<currHP<<")" "! (-" << damage <<  ")" << endl; 
            return false;
        }
    }
    cout << this->getNamewithHP() << " ATTACKED " << player->getFullName() << "("<<currHP<<")" "! (-0)" << endl;
    return false;

}

std::string Player::getNamewithHP() const{
    std::string hp = std::to_string(HP);
    return this->getFullName() + "(" + hp + ")";
}


