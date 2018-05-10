#include "Ambusher.h"
#include "Entity.h"
#include <iostream>
#include <vector>
#include "string.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Ambusher::Ambusher(uint id,int x,int y):Player(id,x,y){
    this -> armor = NOARMOR;
    this -> weapon = SEMIAUTO;
}

Armor Ambusher::getArmor() const {
    return NOARMOR;
}

Weapon Ambusher::getWeapon() const {
    return SEMIAUTO;
}

std::vector<Move> Ambusher::getPriorityList() const{
    std::vector<Move> m;
    m.push_back(ATTACK);
    return m;
}

std::string const Ambusher::getFullName() const{
    std::string fullname;
    fullname = "Ambusher" + this->getBoardID();
    return fullname;
}
Color::Code Ambusher::getColorID() const { return Color::AMBUSHER;}
