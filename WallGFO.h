#ifndef _WallGFO_h_
#define _WallGFO_h_

#include "GameFieldObject.h"
#include "GameField.h"

#define WALL_AROUND_GAME_FIELD 1
#define WALL_GF_CODE 1

class WallGFO : GameFieldObject {
private:
    unsigned wayOfSetting;
    unsigned char wallUCharSymbol;
public:
    WallGFO();
    int setOnGameField(GameField& gf);
    ~WallGFO() = default;
};

#endif
