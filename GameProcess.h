#ifndef _GameProcess_
#define _GameProcess_
#include "GameField.h"
#include "WallGFO.h"
#include "SnakeGFO.h"
#include "User.h"
#include "ConsoleSwitcher.h"

class GameProcess {
    GameField gf;
    User user;
    WallGFO wall;
    SnakeGFO snake;
    int the_end_flag;
public:
    GameProcess();
    ~GameProcess();
    int it_is_the_end();
    int setUserWillByKey(enum keys key);
    int doGameProcessStep();
    GameField& getGameField();
};

#endif
