#ifndef _SnakeGFO_h_
#define _SnakeGFO_h_

#include "GameFieldObject.h"
#include "GameField.h"

#define SNAKE_GF_CODE 2

class SnakeGFO : GameFieldObject {
private:
    unsigned char snakeGFCode;
public:
    SnakeGFO();
    int setOnGameField(GameField& gf);
    ~SnakeGFO() = default;
};

#endif
