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

int SnakeGFO::setHeadCoordsXY(unsigned headCoordsXY[2]) {
    this->headCoordsXY[0] = headCoordsXY[0];
    this->headCoordsXY[1] = headCoordsXY[1];
    this->head_and_tail.push_front(new Coords(headCoordsXY[0], headCoordsXY[1]));
    return 0;
}

int SnakeGFO::getHeadCoordsXY(Coords& headCoords) {
    headCoords.setValueXY(this->headCoordsXY[0], this->headCoordsXY[1]);
    return 0;
}

int SnakeGFO::setOnGameField(GameField& gf) {
    for(list<Coords*>::iterator it = this->head_and_tail.begin();
        it != this->head_and_tail.end();
        it++)
    {
        unsigned coordsXY[2];
        (*it)->getValueXY(coordsXY[0], coordsXY[1]);
        gf.setValueByCoordsXY((unsigned)this->snakeGFCode, coordsXY);
    }
    return 0;
}

int SnakeGFO::removeFromGameField(GameField& gf) {
    for(list<Coords*>::iterator it = this->head_and_tail.begin();
        it != this->head_and_tail.end();
        it++)
    {
        unsigned coordsXY[2];
        (*it)->getValueXY(coordsXY[0], coordsXY[1]);
        gf.setValueByCoordsXY(EMPTY_GF_CODE, coordsXY);
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
    unsigned XY[2];
    XY[0] = this->headCoordsXY[0];
    XY[1] = this->headCoordsXY[1];
    
    switch(this->moveDirection) {
        case SNAKE_MOVE_UP:
            XY[1] -= 1;
            break;
        case SNAKE_MOVE_DOWN:
            XY[1] += 1;
            break;
        case SNAKE_MOVE_RIGHT:
            XY[0] += 1;
            break;
        case SNAKE_MOVE_LEFT:
            XY[0] -= 1;
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
            this->headCoordsXY[1] -= 1;
            break;
        case SNAKE_MOVE_DOWN:
            this->headCoordsXY[1] += 1;
            break;
        case SNAKE_MOVE_RIGHT:
            this->headCoordsXY[0] += 1;
            break;
        case SNAKE_MOVE_LEFT:
            this->headCoordsXY[0] -= 1;
            break;
    }
    
    if(SNAKE_CANT_EAT == this->canEat) {
        Coords* new_head = this->head_and_tail.back();
        this->head_and_tail.pop_back();
        new_head->setValueXY(this->headCoordsXY[0], this->headCoordsXY[1]);
        this->head_and_tail.push_front(new_head);
    } else if(SNAKE_CAN_EAT == this->canEat) {
        Coords* new_head = new Coords(this->headCoordsXY[0], this->headCoordsXY[1]);
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
