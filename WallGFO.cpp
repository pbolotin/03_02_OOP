#include <iostream>
#include "WallGFO.h"

using namespace std;

WallGFO::WallGFO(): wayOfSetting(WALL_AROUND_GAME_FIELD), wallUCharSymbol(WALL_GF_CODE) {}

int WallGFO::setOnGameField(GameField& gf) {
    unsigned sizeXY[2];
    gf.getSizeXY(sizeXY);
    if(WALL_AROUND_GAME_FIELD == this->wayOfSetting) {
        unsigned coordsXY[2];
        for(unsigned i = 0; i < sizeXY[0]; i++) {
            coordsXY[0] = i;
            coordsXY[1] = 0;
            gf.setValueByCoordsXY(WALL_GF_CODE, coordsXY);
            coordsXY[1] = sizeXY[1]-1;
            gf.setValueByCoordsXY(WALL_GF_CODE, coordsXY);
        }
        for(unsigned j = 1; j < sizeXY[1] - 1; j++) {
            coordsXY[0] = 0;
            coordsXY[1] = j;
            gf.setValueByCoordsXY(WALL_GF_CODE, coordsXY);
            coordsXY[0] = sizeXY[0]-1;
            gf.setValueByCoordsXY(WALL_GF_CODE, coordsXY);
        }
    }
    return 0;
}

int WallGFO::removeFromGameField(GameField& gf) {
    unsigned sizeXY[2];
    gf.getSizeXY(sizeXY);
    if(WALL_AROUND_GAME_FIELD == this->wayOfSetting) {
        unsigned coordsXY[2];
        for(unsigned i = 0; i < sizeXY[0]; i++) {
            coordsXY[0] = i;
            coordsXY[1] = 0;
            gf.setValueByCoordsXY(EMPTY_GF_CODE, coordsXY);
            coordsXY[1] = sizeXY[1]-1;
            gf.setValueByCoordsXY(EMPTY_GF_CODE, coordsXY);
        }
        for(unsigned j = 1; j < sizeXY[1] - 1; j++) {
            coordsXY[0] = 0;
            coordsXY[1] = j;
            gf.setValueByCoordsXY(EMPTY_GF_CODE, coordsXY);
            coordsXY[0] = sizeXY[0]-1;
            gf.setValueByCoordsXY(EMPTY_GF_CODE, coordsXY);
        }
    }
    return 0;
}
