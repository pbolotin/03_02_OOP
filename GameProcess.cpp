#include "GameProcess.h"
#include <stdio.h>

GameProcess::GameProcess(): the_end_flag(0) {
    printf("GameProcess constructor, initialize game\n");
}

GameProcess::~GameProcess() {
    printf("GameProcess Destructor, finalize game\n");
}

int GameProcess::it_is_the_end() {
    return this->the_end_flag;
}

int GameProcess::setUserWillByKey(enum keys key) {
    /*KEY_s,
    KEY_S,
    KEY_l,
    KEY_L,
    KEY_q,
    KEY_Q,
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_F5,
    KEY_F6,
    UNKNOWN_KEY
    */
    switch(key) {
        case KEY_q:
        case KEY_Q:
            this->user.setLastWill(USER_WANT_GAME_QUIT);
            break;
        case KEY_UP:
            this->user.setLastWill(USER_WANT_SNAKE_UP);
            break;
        case KEY_DOWN:
            this->user.setLastWill(USER_WANT_SNAKE_DOWN);
            break;
        case KEY_RIGHT:
            this->user.setLastWill(USER_WANT_SNAKE_RIGHT);
            break;
        case KEY_LEFT:
            this->user.setLastWill(USER_WANT_SNAKE_LEFT);
            break;
        default:
            this->user.setLastWill(USER_WANT_NOTHING);
            break;
    }
    return 0;
}

int GameProcess::doGameProcessStep() {
    if(this->user.getLastWill() == USER_WANT_GAME_QUIT) {
        this->the_end_flag = 1;
    }
    if(this->user.getLastWill() == USER_WANT_SNAKE_UP) {
        this->wall.toPlaceOnGameField(this->gf);
    }
    return 0;
}

GameField& GameProcess::getGameField() {
    return this->gf;
}
