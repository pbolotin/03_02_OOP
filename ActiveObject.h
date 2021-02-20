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
