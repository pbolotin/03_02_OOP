#include <iostream>
#include "WallGFO.h"
#include "Coords.h"

using namespace std;

WallGFO::WallGFO(): wayOfSetting(WALL_AROUND_GAME_FIELD) {}

int WallGFO::setOnGameField(GameField& gf) {
    unsigned sizeXY[2];
    gf.getSizeXY(sizeXY);
    if(WALL_AROUND_GAME_FIELD == this->wayOfSetting) {
        Coords coordsXY;
        for(unsigned i = 0; i < sizeXY[0]; i++) {
            coordsXY.setValueXY(i, 0);
            gf.setValueByCoordsXY(WALL_GF_CODE, coordsXY);
            coordsXY.setValueXY(coordsXY.getX(), sizeXY[1]-1);
            gf.setValueByCoordsXY(WALL_GF_CODE, coordsXY);
        }
        for(unsigned j = 1; j < sizeXY[1] - 1; j++) {
            coordsXY.setValueXY(0, j);
            gf.setValueByCoordsXY(WALL_GF_CODE, coordsXY);
            coordsXY.setValueXY(sizeXY[0]-1, coordsXY.getY());
            gf.setValueByCoordsXY(WALL_GF_CODE, coordsXY);
        }
    }
    return 0;
}

int WallGFO::removeFromGameField(GameField& gf) {
    unsigned sizeXY[2];
    gf.getSizeXY(sizeXY);
    if(WALL_AROUND_GAME_FIELD == this->wayOfSetting) {
        Coords coordsXY;
        for(unsigned i = 0; i < sizeXY[0]; i++) {
            coordsXY.setValueXY(i, 0);
            gf.setValueByCoordsXY(EMPTY_GF_CODE, coordsXY);
            coordsXY.setValueXY(coordsXY.getX(), sizeXY[1]-1);
            gf.setValueByCoordsXY(EMPTY_GF_CODE, coordsXY);
        }
        for(unsigned j = 1; j < sizeXY[1] - 1; j++) {
            coordsXY.setValueXY(0, j);
            gf.setValueByCoordsXY(EMPTY_GF_CODE, coordsXY);
            coordsXY.setValueXY(sizeXY[0]-1, coordsXY.getY());
            gf.setValueByCoordsXY(EMPTY_GF_CODE, coordsXY);
        }
    }
    return 0;
}
