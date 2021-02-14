#ifndef _WallGFO_h_
#define _WallGFO_h_

#include "GameFieldObject.h"
#include "GameField.h"

#define WALL_AROUND_GAME_FIELD 1
#define WALL_MATRIX_VALUE 1

class WallGFO : GameFieldObject {
private:
    unsigned wayToPlace;
    unsigned char wallUCharSymbol;
public:
    WallGFO();
    int toPlaceOnGameField(GameField& gf);
    ~WallGFO() = default;
};

#endif
