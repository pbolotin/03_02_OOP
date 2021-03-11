#ifndef _ActiveObject_
#define _ActiveObject_

#include "ActiveObject.h"
#include "User.h"
#include "GameField.h"
#include "Ticker.h"

/* Abstract */

class ActiveObject {
public:
    virtual int reactOnUser(User&) = 0;
    virtual int reactOnGameField(GameField&) = 0;
    virtual int reactOnTicker(Ticker&) = 0;
    virtual ~ActiveObject() = default;
};

#endif
#ifndef _ConsoleSwitcher_h_
#define _ConsoleSwitcher_h_

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum keys {
    KEY_s,
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
};

#define READ_BUFFER_SIZE 1024

typedef struct seq_element {
    int code;
    long time;
} seq_element;

#define _HOW_MANY_CODES_SEQ 12

#define TIMEOUT_TO_NEW_KEY_NANOSEC 100000000

class ConsoleSwitcher {
private:
    ConsoleSwitcher();
    static struct termios myTermStruct;
    static char* _key_code_sequences[];

    static int _my_ncmp(char* s1, char* s2, int how_many);
    static int _rk_symbol_analysis(char* read_as_str);
    static int rk_readkey(enum keys *key);
    static int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);
public:
    static int storeCurrentTerminalState();
    static int setNotCanonicalTerminalState();
    static int clearTerminalScreen();
    static int restoreTerminalState();
    static enum keys getLastKeyFromTerminal();
};

#endif
#ifndef _Coords_h_
#define _Coords_h_

#include <limits>

class Coords {
    unsigned   x;
    unsigned   y;
public:
    Coords();
    Coords(unsigned x, unsigned y);
    Coords(Coords& coords);
    Coords& operator=(Coords &) = default;
    int getValueXY(unsigned& x, unsigned& y);
    unsigned getX();
    unsigned getY();
    int setValueXY(unsigned x, unsigned y);
    int up();
    int down();
    int right();
    int left();
    ~Coords();
};

#endif

#ifndef _FoodGFO_h_
#define _FoodGFO_h_

#include "GameFieldObject.h"
#include "GameField.h"
#include "Coords.h"

#define FOOD_GF_CODE 3

#define FOOD_PLACED 1
#define FOOD_NOT_PLACED 0

#define FOOD_PLACE_FOUND 1
#define FOOD_PLACE_NOT_FOUND 0

class FoodGFO : public GameFieldObject {
private:
    Coords XY;
    Coords foundXY;
    unsigned placed;
    unsigned found;
public:
    FoodGFO();
    int check_if_placed();
    int check_if_found();
    int is_on_gf_yet(GameField& gf);
    int findCoordsForFood(GameField& gf, Coords& snakeHead);
    int prepareFoundToSet();
    int setOnGameField(GameField& gf);
    int removeFromGameField(GameField& gf);
    ~FoodGFO() = default;
};

#endif
#ifndef _GameField_
#define _GameField_

#include "Coords.h"

#define EMPTY_GF_CODE 0

class GameField {
    unsigned   sizeX;
    unsigned   sizeY;
    unsigned** matrix;
    
    int initializeMatrix();
public:
    GameField();
    GameField(unsigned sizeX, unsigned sizeY);
    int getSizeXY(unsigned sizeXY[]);
    int getValueByCoordsXY(unsigned *value, Coords& coordsXY);
    int setValueByCoordsXY(unsigned, Coords& coordsXY);
    ~GameField();
};

#endif

#ifndef _GameFieldObject_
#define _GameFieldObject_

#include "GameField.h"

/* Abstract */

class GameFieldObject {
public:
    virtual int setOnGameField(GameField&) = 0;
    virtual int removeFromGameField(GameField&) = 0;
    virtual ~GameFieldObject() = default;
};

#endif
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
#ifndef _GameRepresentator_
#define _GameRepresentator_

#include "GameField.h"

class GameRepresentator {
public:
    GameRepresentator();
    int outputGameFieldOnTerminal(GameField& gf);
    int outputGameResultOnTerminal(GameField& gf, int result);
    ~GameRepresentator();
};

#endif
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
    
    Coords headCoordsXY;
    std::list<Coords*> head_and_tail;
public:
    SnakeGFO();
    int reactOnUser(User& ur);
    int reactOnGameField(GameField& gf);
    int reactOnTicker(Ticker& tr);
    
    int setHeadCoordsXY(Coords& headCoordsXY);
    int getHeadCoordsXY(Coords& headCoords);
    
    int setOnGameField(GameField& gf);
    int removeFromGameField(GameField& gf);
    
    int getLength();
    
    int move();
    int check_if_finish();
    ~SnakeGFO();
};

#endif
#ifndef _Ticker_h_
#define _Ticker_h_

class Ticker {
private:
    unsigned long tick_length;
    unsigned long tick_counter;
public:
    Ticker();
    Ticker(unsigned long tick_length);
    Ticker(unsigned long tick_length, unsigned long tick_counter);
    int do_tick();
    unsigned long getTickCount();
};

#endif
#ifndef _User_h_
#define _User_h_

#define USER_WANT_NOTHING     0
#define USER_WANT_SNAKE_UP    1
#define USER_WANT_SNAKE_DOWN  2
#define USER_WANT_SNAKE_LEFT  3
#define USER_WANT_SNAKE_RIGHT 4
#define USER_WANT_GAME_QUIT   10
#define USER_WANT_GAME_PAUSE  11

class User {
private:
    int the_last_will;
public:
    User();
    void setLastWill(int last_will);
    int getLastWill();
};

#endif
#ifndef _WallGFO_h_
#define _WallGFO_h_

#include "GameFieldObject.h"
#include "GameField.h"

#define WALL_AROUND_GAME_FIELD 1
#define WALL_GF_CODE 1

class WallGFO : public GameFieldObject {
private:
    unsigned wayOfSetting;
public:
    WallGFO();
    int setOnGameField(GameField& gf);
    int removeFromGameField(GameField& gf);
    ~WallGFO() = default;
};

#endif
#ifndef _SNAKE_H_
#define _SNAKE_H_

#endif _SNAKE_H_
