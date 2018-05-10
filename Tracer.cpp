#include "Tracer.h"
#include "Entity.h"
#include <vector>
#include <iostream>
#include "string.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Tracer::Tracer(uint id,int x,int y):Player(id,x,y){
    this -> armor = BRICK;
    this -> weapon = SHOVEL;
}

Armor Tracer::getArmor() const {
    return BRICK;
}

Weapon Tracer::getWeapon() const {
    return SHOVEL;
}

std::vector<Move> Tracer::getPriorityList() const{
    std::vector<Move> m;
    m.push_back(UP);
    m.push_back(LEFT);
    m.push_back(DOWN);
    m.push_back(RIGHT);
    m.push_back(ATTACK);
    return m;
}

std::string const Tracer::getFullName() const{
    std::string fullname;
    fullname = "Tracer" + this->getBoardID();
    return fullname;
}

 Color::Code Tracer::getColorID() const { return Color::TRACER; }