#ifndef _WallGFO_h_
#define _WallGFO_h_

#include "GameFieldObject.h"
#include "GameField.h"

class WallGFO : GameFieldObject {
private:

public:
    int placeOnGameField(GameField& gf);
    ~WallGFO() = default;
};

#endif
