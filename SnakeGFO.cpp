#include <iostream>
#include "WallGFO.h"
#include "SnakeGFO.h"
#include "FoodGFO.h"

using namespace std;

SnakeGFO::SnakeGFO(): snakeGFCode(SNAKE_GF_CODE),
                      moveDirection(SNAKE_MOVE_UP),
                      canMove(SNAKE_CAN_MOVE),
                      canEat(SNAKE_CANT_EAT),
                      tickReductorQuotient(SNAKE_TICK_REDUCTOR),
                      finishFlag(SNAKE_NOT_FINISH)
{}

int SnakeGFO::setHeadCoordsXY(Coords& headCoordsXY) {
    this->headCoordsXY = headCoordsXY;
    this->head_and_tail.push_front(new Coords(headCoordsXY));
    return 0;
}

int SnakeGFO::getHeadCoordsXY(Coords& headCoords) {
    headCoords = this->headCoordsXY;
    return 0;
}

int SnakeGFO::setOnGameField(GameField& gf) {
    for(list<Coords*>::iterator it = this->head_and_tail.begin();
        it != this->head_and_tail.end();
        it++)
    {
        gf.setValueByCoordsXY((unsigned)this->snakeGFCode, *(*it));
    }
    return 0;
}

int SnakeGFO::removeFromGameField(GameField& gf) {
    for(list<Coords*>::iterator it = this->head_and_tail.begin();
        it != this->head_and_tail.end();
        it++)
    {
        gf.setValueByCoordsXY(EMPTY_GF_CODE, *(*it));
    }
    return 0;
}

int SnakeGFO::reactOnUser(User& ur) {
    switch(ur.getLastWill()) {
        case USER_WANT_SNAKE_UP:
            if(this->moveDirection != SNAKE_MOVE_DOWN) {
                this->moveDirection = SNAKE_MOVE_UP;
            }
            break;
        case USER_WANT_SNAKE_DOWN:
            if(this->moveDirection != SNAKE_MOVE_UP) {
                this->moveDirection = SNAKE_MOVE_DOWN;
            }
            break;
        case USER_WANT_SNAKE_RIGHT:
            if(this->moveDirection != SNAKE_MOVE_LEFT) {
                this->moveDirection = SNAKE_MOVE_RIGHT;
            }
            break;
        case USER_WANT_SNAKE_LEFT:
            if(this->moveDirection != SNAKE_MOVE_RIGHT) {
                this->moveDirection = SNAKE_MOVE_LEFT;
            }
            break;
    }
    return 0;
}

int SnakeGFO::reactOnGameField(GameField& gf) {
    Coords XY;
    XY = this->headCoordsXY;
    
    switch(this->moveDirection) {
        case SNAKE_MOVE_UP:
            XY.up();
            break;
        case SNAKE_MOVE_DOWN:
            XY.down();
            break;
        case SNAKE_MOVE_RIGHT:
            XY.right();
            break;
        case SNAKE_MOVE_LEFT:
            XY.left();
            break;
    }
    
    unsigned value;
    gf.getValueByCoordsXY(&value, XY);
    
    switch(value) {
        case EMPTY_GF_CODE:
            this->canMove = SNAKE_CAN_MOVE;
            break;
        case WALL_GF_CODE:
            this->canMove = SNAKE_CANT_MOVE;
            break;
        case SNAKE_GF_CODE:
            this->canMove = SNAKE_CANT_MOVE;
            break;
        case FOOD_GF_CODE:
            this->canMove = SNAKE_CAN_MOVE;
            this->canEat = SNAKE_CAN_EAT;
            break;
        default:
            this->canMove = SNAKE_CANT_MOVE;
            break;
    }
    
    return 0;
}

int SnakeGFO::reactOnTicker(Ticker& tr) {
    unsigned long tc = tr.getTickCount();
    if(0 == tc % this->tickReductorQuotient) {
        if(SNAKE_CANT_MOVE == this->canMove) {
            this->finishFlag = SNAKE_FINISH;
        } else {
            this->move();
        }
    }
    return 0;
}

int SnakeGFO::getLength() {
    return this->head_and_tail.size();
}

int SnakeGFO::move() {
    switch(this->moveDirection) {
        case SNAKE_MOVE_UP:
            this->headCoordsXY.up();
            break;
        case SNAKE_MOVE_DOWN:
            this->headCoordsXY.down();
            break;
        case SNAKE_MOVE_RIGHT:
            this->headCoordsXY.right();
            break;
        case SNAKE_MOVE_LEFT:
            this->headCoordsXY.left();
            break;
    }
    
    if(SNAKE_CANT_EAT == this->canEat) {
        Coords* new_head = this->head_and_tail.back();
        this->head_and_tail.pop_back();
        *new_head = this->headCoordsXY;
        this->head_and_tail.push_front(new_head);
    } else if(SNAKE_CAN_EAT == this->canEat) {
        Coords* new_head = new Coords(this->headCoordsXY);
        this->head_and_tail.push_front(new_head);
        this->canEat = SNAKE_CANT_EAT;
    }
    
    return 0;
}

int SnakeGFO::check_if_finish() {
    if(SNAKE_FINISH == this->finishFlag) {
        return 1;
    } else return 0;
}

SnakeGFO::~SnakeGFO() {
    while(!this->head_and_tail.empty()) {
        delete this->head_and_tail.back();
        this->head_and_tail.pop_back();
    }
}
