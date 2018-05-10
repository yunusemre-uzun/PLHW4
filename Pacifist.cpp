#include "Pacifist.h"
#include "Entity.h"
#include <vector>
#include <iostream>
#include "string.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Pacifist::Pacifist(uint id,int x,int y):Player(id,x,y){
    this -> armor = METAL;
    this -> weapon = NOWEAPON;
}

Armor Pacifist::getArmor() const {
    return METAL;
}

Weapon Pacifist::getWeapon() const {
    return NOWEAPON;
}

std::vector<Move> Pacifist::getPriorityList() const{
    std::vector<Move> m;
    m.push_back(UP);
    m.push_back(LEFT);
    m.push_back(DOWN);
    m.push_back(RIGHT);
    return m;
}

std::string const Pacifist::getFullName() const{
    std::string fullname;
    fullname = "Pacifist" + this->getBoardID();
    return fullname;
}

Color::Code Pacifist::getColorID() const { return Color::PACIFIST; }