#include <stdio.h>
#include <iostream>
#include "GameRepresentator.h"
#include "WallGFO.h"
#include "SnakeGFO.h"

using namespace std;

GameRepresentator::GameRepresentator() {
    printf("GameRepresentator constructor will need the game state to represent it\n");
}

int GameRepresentator::outputGameFieldOnTerminal(GameField& gf) {
    unsigned sizeXY[2];
    unsigned coordsXY[2];
    unsigned value = 0;
    gf.getSizeXY(sizeXY);
    unsigned char* longStr = new unsigned char[(sizeXY[0]+1) * sizeXY[1]];
    unsigned placeInStr = 0;
    for(unsigned j = 0; j < sizeXY[1]; j++) {
        for(unsigned i = 0; i < sizeXY[0]; i++) {
            coordsXY[0] = i;
            coordsXY[1] = j;
            gf.getValueByCoordsXY(&value, coordsXY);
            switch(value) {
                case WALL_GF_CODE:
                    longStr[placeInStr] = '*';
                    break;
                case SNAKE_GF_CODE:
                    longStr[placeInStr] = 'S';
                    break;
                case EMPTY_GF_CODE:
                    longStr[placeInStr] = ' ';
                    break;
                default:
                    longStr[placeInStr] = 'E';
            }
            placeInStr++;
        }
        longStr[placeInStr] = '\n';
        placeInStr++;
    }
    cout << longStr;
    delete [] longStr;
    return 0;
}

GameRepresentator::~GameRepresentator() {
    printf("GameRepresentator will finilize itself\n");
}
