#ifndef _FoodGFO_h_
#define _FoodGFO_h_

#include "GameFieldObject.h"
#include "GameField.h"
#include "Coords.h"

#define FOOD_GF_CODE 3

class FoodGFO : GameFieldObject {
private:
    Coords XY;
    Coords foundXY;
    unsigned eaten;
    unsigned placed;
public:
    FoodGFO();
    int findCoordsForFood(GameField& gf, Coords& snakeHead);
    int setOnGameField(GameField& gf);
    int removeFromGameField(GameField& gf);
    ~FoodGFO() = default;
};

#endif
