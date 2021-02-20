#include <iostream>
#include "WallGFO.h"
#include "SnakeGFO.h"

using namespace std;

SnakeGFO::SnakeGFO(): snakeGFCode(SNAKE_GF_CODE) {}

int SnakeGFO::setOnGameField(GameField& gf) {
    unsigned sizeXY[2];
    gf.getSizeXY(sizeXY);
    
    unsigned coordsXY[2];
    coordsXY[0] = sizeXY[0]/2;
    coordsXY[1] = sizeXY[1]/2;
    gf.setValueByCoordsXY((unsigned)this->snakeGFCode, coordsXY);
    
    return 0;
}
