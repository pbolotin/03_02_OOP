#ifndef _SnakeGFO_h_
#define _SnakeGFO_h_

#include <list>
#include "Coords.h"
#include "GameFieldObject.h"
#include "ActiveObject.h"
#include "GameField.h"

#define SNAKE_TICK_REDUCTOR 10

#define SNAKE_GF_CODE       2

#define SNAKE_MOVE_UP       1
#define SNAKE_MOVE_DOWN     2
#define SNAKE_MOVE_LEFT     3
#define SNAKE_MOVE_RIGHT    4

#define SNAKE_CAN_MOVE      1
#define SNAKE_CANT_MOVE     0

#define SNAKE_FINISH        1
#define SNAKE_NOT_FINISH    0

#define SNAKE_CAN_EAT       1
#define SNAKE_CANT_EAT      0

class SnakeGFO : public GameFieldObject, ActiveObject {
private:
    unsigned char snakeGFCode;
    unsigned moveDirection;
    unsigned canMove;
    unsigned canEat;
    unsigned tickReductorQuotient;
    unsigned finishFlag;
    
    unsigned headCoordsXY[2];
    std::list<Coords*> head_and_tail;
public:
    SnakeGFO();
    int reactOnUser(User& ur);
    int reactOnGameField(GameField& gf);
    int reactOnTicker(Ticker& tr);
    
    int setHeadCoordsXY(unsigned headCoordsXY[2]);
    int getHeadCoordsXY(Coords& headCoords);
    
    int setOnGameField(GameField& gf);
    int removeFromGameField(GameField& gf);
    
    int getLength();
    
    int move();
    int check_if_finish();
    ~SnakeGFO();
};

#endif
