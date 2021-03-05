#include "GameProcess.h"
#include <stdio.h>

GameProcess::GameProcess(): ticker(GP_TICKER_DEFAULT), the_end_flag(0)
{
    printf("GameProcess constructor, initialize game\n");
    
    unsigned sizeXY[2];
    this->gf.getSizeXY(sizeXY);
    
    unsigned coordsXY[2];
    coordsXY[0] = sizeXY[0]/2;
    coordsXY[1] = sizeXY[1]/2;
    
    this->snake.setHeadCoordsXY(coordsXY);
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
    int user_will = this->user.getLastWill();
    if(user_will == USER_WANT_GAME_QUIT) {
        this->the_end_flag = 1;
    }
    if(this->snake.check_if_finish()) {
        printf("SNAKE IS FINISHED!\n");
        this->the_end_flag = 1;
    }
    this->wall.setOnGameField(this->gf);
    this->snake.removeFromGameField(this->gf);
    this->snake.reactOnUser(this->user);
    this->snake.reactOnGameField(this->gf);    
    this->snake.reactOnTicker(this->ticker);
    
    this->snake.setOnGameField(this->gf);
    return 0;
}

int GameProcess::doGamePause() {
    return this->ticker.do_tick();
}

GameField& GameProcess::getGameField() {
    return this->gf;
}
