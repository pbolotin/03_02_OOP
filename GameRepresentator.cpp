#include <stdio.h>
#include <iostream>
#include <cstring>
#include "GameRepresentator.h"
#include "WallGFO.h"
#include "SnakeGFO.h"
#include "FoodGFO.h"

using namespace std;

GameRepresentator::GameRepresentator() {
    //printf("GameRepresentator constructor will need the game state to represent it\n");
}

int GameRepresentator::outputGameFieldOnTerminal(GameField& gf) {
    unsigned sizeXY[2];
    Coords coordsXY;
    unsigned value = 0;
    gf.getSizeXY(sizeXY);
    unsigned char* longStr = new unsigned char[(sizeXY[0]+1) * sizeXY[1]];
    unsigned placeInStr = 0;
    for(unsigned j = 0; j < sizeXY[1]; j++) {
        for(unsigned i = 0; i < sizeXY[0]; i++) {
            coordsXY.setValueXY(i, j);
            gf.getValueByCoordsXY(&value, coordsXY);
            switch(value) {
                case EMPTY_GF_CODE:
                    longStr[placeInStr] = ' ';
                    break;
                case WALL_GF_CODE:
                    longStr[placeInStr] = 'W';
                    break;
                case SNAKE_GF_CODE:
                    longStr[placeInStr] = 'S';
                    break;
                case FOOD_GF_CODE:
                    longStr[placeInStr] = 'F';
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

int GameRepresentator::outputGameResultOnTerminal(GameField& gf, int result) {
    unsigned sizeXY[2];
    gf.getSizeXY(sizeXY);
    
    unsigned middleStrY = sizeXY[1]/2;
    char result_str_place[100];
    char topic[] = "!SCORE!";
    sprintf(result_str_place, "  !%d!", result);
    unsigned res_length = strlen(result_str_place);
    unsigned k = 0;
    unsigned l = 0;
    int flag_can_put = 0;
    if(res_length <= sizeXY[0]) {
        flag_can_put = 1;
    }
    
    unsigned char* longStr = new unsigned char[(sizeXY[0]+1) * sizeXY[1]];
    unsigned placeInStr = 0;
    for(unsigned j = 0; j < sizeXY[1]; j++) {
        for(unsigned i = 0; i < sizeXY[0]; i++) {
            if(j == middleStrY-1 && l < strlen(topic)) {
                longStr[placeInStr] = topic[l];
                l++;
            } else if(j == middleStrY && flag_can_put && k < res_length) {
                longStr[placeInStr] = result_str_place[k];
                k++;
            } else {
                longStr[placeInStr] = ' ';
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
    //printf("GameRepresentator will finilize itself\n");
}
