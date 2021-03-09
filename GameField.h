#ifndef _GameField_
#define _GameField_

#include "Coords.h"

#define EMPTY_GF_CODE 0

class GameField {
    unsigned   sizeX;
    unsigned   sizeY;
    unsigned** matrix;
    
    int initializeMatrix();
public:
    GameField();
    GameField(unsigned sizeX, unsigned sizeY);
    int getSizeXY(unsigned sizeXY[]);
    int getValueByCoordsXY(unsigned *value, Coords& coordsXY);
    int setValueByCoordsXY(unsigned, Coords& coordsXY);
    ~GameField();
};

#endif

