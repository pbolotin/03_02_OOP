#ifndef _GameField_
#define _GameField_

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
    int getValueByCoordsXY(unsigned *, unsigned[]);
    int setValueByCoordsXY(unsigned, unsigned[]);
    ~GameField();
};

#endif

