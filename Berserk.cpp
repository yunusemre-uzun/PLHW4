#include "Berserk.h"
#include "Entity.h"
#include <vector>
#include <iostream>
#include "string.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Berserk::Berserk(uint id,int x,int y):Player(id,x,y){
    this -> armor = WOODEN;
    this -> weapon = PISTOL;
}

Armor Berserk::getArmor() const {
    return WOODEN;
}

Weapon Berserk::getWeapon() const {
    return PISTOL;
}

std::vector<Move> Berserk::getPriorityList() const{
    std::vector<Move> m;
    m.push_back(ATTACK);
    m.push_back(UP);
    m.push_back(LEFT);
    m.push_back(DOWN);
    m.push_back(RIGHT);
    return m;
}

std::string const Berserk::getFullName() const{
    std::string fullname;
    fullname = "Berserk" + this->getBoardID();
    return fullname;
}

Color::Code Berserk::getColorID() const { return Color::BERSERK; };
