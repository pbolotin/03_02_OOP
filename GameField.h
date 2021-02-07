#ifndef _GameField_
#define _GameField_

class GameField {
    unsigned   sizeX;
    unsigned   sizeY;
    unsigned** matrix;
    
    int initializeMatrix();
public:
    GameField();
    GameField(unsigned sizeX, unsigned sizeY);
    ~GameField();
};

#endif
