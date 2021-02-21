#include <iostream>
#include "WallGFO.h"
#include "SnakeGFO.h"

using namespace std;

SnakeGFO::SnakeGFO(): snakeGFCode(SNAKE_GF_CODE), moveDirection(SNAKE_MOVE_UP) {}

int SnakeGFO::setOnGameField(GameField& gf) {
    unsigned sizeXY[2];
    gf.getSizeXY(sizeXY);
    
    unsigned coordsXY[2];
    coordsXY[0] = sizeXY[0]/2;
    coordsXY[1] = sizeXY[1]/2;
    gf.setValueByCoordsXY((unsigned)this->snakeGFCode, coordsXY);
    
    return 0;
}

int SnakeGFO::reactOnGameField(GameField& gf) {
    unsigned coordsXY[2];
    coordsXY[0] = 0;
    coordsXY[1] = 0;
    unsigned value;
    gf.getValueByCoordsXY(&value, coordsXY);
    return 0;
}

int SnakeGFO::reactOnUser(User& ur) {
    switch(ur.getLastWill()) {
        case USER_WANT_SNAKE_UP:
            this->moveDirection = SNAKE_MOVE_UP;
            break;
        case USER_WANT_SNAKE_DOWN:
            this->moveDirection = SNAKE_MOVE_DOWN;
            break;
        case USER_WANT_SNAKE_RIGHT:
            this->moveDirection = SNAKE_MOVE_RIGHT;
            break;
        case USER_WANT_SNAKE_LEFT:
            this->moveDirection = SNAKE_MOVE_LEFT;
            break;
    }
    return 0;
}

int SnakeGFO::reactOnTicker(Ticker& tr) {
    unsigned long tc = tr.getTickCount();
    return tc;
}
