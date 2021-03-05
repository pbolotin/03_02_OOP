#ifndef _GameProcess_
#define _GameProcess_

#include "Ticker.h"
#include "GameField.h"
#include "WallGFO.h"
#include "SnakeGFO.h"
#include "FoodGFO.h"
#include "User.h"
#include "ConsoleSwitcher.h"

#define GP_TICKER_DEFAULT 100000

class GameProcess {
    Ticker ticker;
    GameField gf;
    User user;
    WallGFO wall;
    SnakeGFO snake;
    FoodGFO food;
    int the_end_flag;
public:
    GameProcess();
    ~GameProcess();
    int it_is_the_end();
    int setUserWillByKey(enum keys key);
    int doGameProcessStep();
    int doGamePause();
    GameField& getGameField();
};

#endif
