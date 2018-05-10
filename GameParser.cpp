#include "GameParser.h"
#include "Player.h"
#include "Berserk.h"
#include "Ambusher.h"
#include "Dummy.h"
#include "Pacifist.h"
#include "Tracer.h"
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

std::pair<int, std::vector<Player *> *> GameParser::parseFileWithName(const std::string& filename){
    std::string line;
    std::ifstream inpfile (filename);
    std::vector<Player *> *v = new std::vector<Player *>;
    size_t boardsize;
    if(inpfile.is_open()){
        getline(inpfile,line); // get the first line
        size_t t = line.find(":");
        std::string tmp;
        tmp = line.substr(t+2);
        boardsize = std::stoi(tmp);
        getline(inpfile,line); // get the second line
        t = line.find(":");
        t += 2 ;
        tmp = line.substr(t);
        int numberofplayers = std::stoi(tmp);
        for(int i=0;i<numberofplayers;i++){ // get the palyers
            getline(inpfile,line);
            size_t t = line.find("::"); // find the first occurence of '::'
            int id = std::stoi(line.substr(0,t));
            size_t t2 = line.find("::",t+2); // second occurence of '::'
            std::string type = line.substr(t+2,t2-t-2);
            t = line.find("::",t2+2); //third occurence of '::'
            int x = std::stoi(line.substr(t2+2,t-t2-2));
            int y = std::stoi(line.substr(t+2));
            //cout << "id:" << id << "  type:" << type << "   x:" << x << "   y:" << y << "   " <<  endl;
            switch(type[0]){
                case 'A':
                    {Ambusher *a = new Ambusher(id,x,y);
                    v->push_back((Player*)a); // add new player to vector
                    break;}
                case 'B':
                    {Berserk *b = new Berserk(id,x,y);
                    v->push_back((Player*)b); // add new player to vector
                    break;}
                case 'D':
                    {Dummy *d = new Dummy(id,x,y);
                    v->push_back((Player*)d); // add new player to vector
                    break;}
                case 'P':
                    {Pacifist *p = new Pacifist(id,x,y);
                    v->push_back((Player*)p); // add new player to vector
                    break;}
                case 'T':
                    {Tracer *t = new Tracer(id,x,y);
                    v->push_back((Player*)t); // add new player to vector
                    break;}
            }
        }
        std::pair<int, std::vector<Player *> *> ret (boardsize,v);
        return ret;
    }
}
