#ifndef _GameFieldObject_
#define _GameFieldObject_

#include "GameField.h"

/* Abstract */

class GameFieldObject {
public:
    virtual int placeOnGameField(GameField&) = 0;
    virtual ~GameFieldObject() = default;
};

#endif
