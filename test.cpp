#include <iostream>
#include "Player.h"
#include "Ambusher.h"
#include "Berserk.h"
#include "Board.h"
#include "Color.h"
#include "Coordinate.h"
#include "Dummy.h"
#include "Entity.h"
#include "GameEngine.h"
#include "GameParser.h"
#include "Pacifist.h"
#include "Tracer.h"
#include "BoardPrinter.h"
#include <unistd.h>

unsigned int microseconds=1000000;


using namespace std;

int main(){
    std::vector<Player *> *p =(GameParser::parseFileWithName("input.txt")).second;
    uint boardSize = (GameParser::parseFileWithName("input.txt")).first;
    cout << boardSize << endl;
    for(int i=0;i<p->size();i++){
        cout << (*p)[i]->getFullName() << "Coords: " << (*p)[i]->getCoord() << endl;
    }
    GameEngine g = GameEngine(boardSize,p);
    BoardPrinter::printBoard(g.getBoard());
    while(!(g.isFinished())){
        g.takeTurn();
        BoardPrinter::printBoard(g.getBoard());
        usleep(microseconds);
        cout << g.getBoard().getHillCoordinates() << endl;;
    }
    return 0;
}