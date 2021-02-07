#ifndef _GameProcess_
#define _GameProcess_
#include "GameField.h"
#include "User.h"

class GameProcess {
    GameField gf;
    User user;
public:
    GameProcess();
    ~GameProcess();
};

#endif
