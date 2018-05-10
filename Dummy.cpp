#include "Dummy.h"
#include "Entity.h"
#include <vector>
#include <iostream>
#include "string.h"
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Dummy::Dummy(uint id,int x,int y):Player(id,x,y){
    this -> armor = NOARMOR;
    this -> weapon = NOWEAPON;
    HP = 1000;
}

Armor Dummy::getArmor() const {
    return NOARMOR;
}

Weapon Dummy::getWeapon() const {
    return NOWEAPON;
}

std::vector<Move> Dummy::getPriorityList() const{
    std::vector<Move> m;
    m.push_back(NOOP);
    return m;
}

std::string const Dummy::getFullName() const{
    std::string fullname;
    fullname = "Dummy" + this->getBoardID();
    return fullname;
}