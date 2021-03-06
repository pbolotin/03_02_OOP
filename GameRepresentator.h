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
