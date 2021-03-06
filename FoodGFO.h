#ifndef _FoodGFO_h_
#define _FoodGFO_h_

#include "GameFieldObject.h"
#include "GameField.h"
#include "Coords.h"

#define FOOD_GF_CODE 3

#define FOOD_PLACED 1
#define FOOD_NOT_PLACED 0

#define FOOD_PLACE_FOUND 1
#define FOOD_PLACE_NOT_FOUND 0

class FoodGFO : GameFieldObject {
private:
    Coords XY;
    Coords foundXY;
    unsigned placed;
    unsigned found;
public:
    FoodGFO();
    int check_if_placed();
    int check_if_found();
    int is_on_gf_yet(GameField& gf);
    int findCoordsForFood(GameField& gf, Coords& snakeHead);
    int prepareFoundToSet();
    int setOnGameField(GameField& gf);
    int removeFromGameField(GameField& gf);
    ~FoodGFO() = default;
};

#endif
