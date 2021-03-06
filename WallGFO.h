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
