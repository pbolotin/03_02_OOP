#ifndef _GameFieldObject_
#define _GameFieldObject_

#include "GameField.h"

/* Abstract */

class GameFieldObject {
public:
    virtual int toPlaceOnGameField(GameField&) = 0;
    virtual ~GameFieldObject() = default;
};

#endif
