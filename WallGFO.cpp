#include <iostream>
#include "WallGFO.h"

using namespace std;

WallGFO::WallGFO(): wayToPlace(WALL_AROUND_GAME_FIELD), wallUCharSymbol(WALL_MATRIX_VALUE) {}

int WallGFO::toPlaceOnGameField(GameField& gf) {
    unsigned sizeXY[2];
    gf.getSizeXY(sizeXY);
    if(WALL_AROUND_GAME_FIELD == this->wayToPlace) {
        unsigned coordsXY[2];
        for(unsigned i = 0; i < sizeXY[0]; i++) {
            coordsXY[0] = i;
            coordsXY[1] = 0;
            gf.toPlaceValueByCoordsXY((unsigned)this->wallUCharSymbol, coordsXY);
            coordsXY[1] = sizeXY[1]-1;
            gf.toPlaceValueByCoordsXY((unsigned)this->wallUCharSymbol, coordsXY);
        }
        for(unsigned j = 1; j < sizeXY[1] - 1; j++) {
            coordsXY[0] = 0;
            coordsXY[1] = j;
            gf.toPlaceValueByCoordsXY((unsigned)this->wallUCharSymbol, coordsXY);
            coordsXY[0] = sizeXY[0]-1;
            gf.toPlaceValueByCoordsXY((unsigned)this->wallUCharSymbol, coordsXY);
        }
    }
    return 0;
}
