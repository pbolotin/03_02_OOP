#ifndef _SnakeGFO_h_
#define _SnakeGFO_h_

#include "GameFieldObject.h"
#include "ActiveObject.h"
#include "GameField.h"


#define SNAKE_GF_CODE       2

#define SNAKE_MOVE_UP       1
#define SNAKE_MOVE_DOWN     2
#define SNAKE_MOVE_LEFT     3
#define SNAKE_MOVE_RIGHT    4

class SnakeGFO : GameFieldObject, ActiveObject {
private:
    unsigned char snakeGFCode;
    unsigned moveDirection;
public:
    SnakeGFO();
    int reactOnGameField(GameField& gf);
    int reactOnUser(User& ur);
    int reactOnTicker(Ticker& tr);
    int setOnGameField(GameField& gf);
    ~SnakeGFO() = default;
};

#endif
