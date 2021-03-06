#ifndef _GameProcess_
#define _GameProcess_

#include <vector>
#include "Ticker.h"
#include "GameFieldObject.h"
#include "GameField.h"
#include "WallGFO.h"
#include "SnakeGFO.h"
#include "FoodGFO.h"
#include "User.h"
#include "ConsoleSwitcher.h"

#define GP_TICKER_DEFAULT 100000

using namespace std;

class GameProcess {
    Ticker ticker;
    GameField gf;
    User user;
    WallGFO wall;
    SnakeGFO snake;
    FoodGFO food;
    vector<GameFieldObject*> allGFO;
    int the_end_flag;
public:
    GameProcess();
    GameProcess(unsigned sizeX, unsigned sizeY, unsigned long tickerUS = GP_TICKER_DEFAULT);
    ~GameProcess();
    int it_is_the_end();
    int getGameResult();
    int setUserWillByKey(enum keys key);
    int doGameProcessStep();
    int doGamePause();
    int doFinish();
    GameField& getGameField();
};

#endif
