#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "FoodGFO.h"

using namespace std;

FoodGFO::FoodGFO(): XY(0,0), foundXY(0,0), placed(FOOD_NOT_PLACED), found(FOOD_PLACE_NOT_FOUND) {}

int FoodGFO::setOnGameField(GameField& gf) {
    gf.setValueByCoordsXY(FOOD_GF_CODE, this->XY);
    this->placed = FOOD_PLACED;
    return 0;
}

int FoodGFO::removeFromGameField(GameField& gf) {
    if(this->is_on_gf_yet(gf)) {
        gf.setValueByCoordsXY(EMPTY_GF_CODE, this->XY);
    }
    this->placed = FOOD_NOT_PLACED;
    return 0;
}

int FoodGFO::findCoordsForFood(GameField& gf, Coords& snakeHead) {
    vector<Coords*> good_places_for_food;
    unsigned sizeXY[2];
    Coords coordsXY;
    Coords headXY;
    unsigned value;
    gf.getSizeXY(sizeXY);
    
    for(unsigned i = 0; i < sizeXY[0]; i++) {
        for(unsigned j = 0; j < sizeXY[1]; j++) {
            coordsXY.setValueXY(i, j);
            gf.getValueByCoordsXY(&value, coordsXY);
            if(value == EMPTY_GF_CODE) {
                headXY = snakeHead;
                if(abs((int)(coordsXY.getX()-headXY.getX())) + abs((int)(coordsXY.getY()-headXY.getY())) > 2) {
                    good_places_for_food.push_back(new Coords(coordsXY));
                }
            }
        }
    }
    
    unsigned sz = good_places_for_food.size();
    if(sz != 0) {
        srand(time(nullptr));
        unsigned pos = rand() % sz;
        this->foundXY = *(good_places_for_food[pos]);
        this->found = FOOD_PLACE_FOUND;
    } else {
        this->found = FOOD_PLACE_NOT_FOUND;
    }
    
    while(!good_places_for_food.empty()) {
        delete good_places_for_food.back();
        good_places_for_food.pop_back();
    }
    return 0;
}

int FoodGFO::prepareFoundToSet() {
    this->XY = this->foundXY;
    this->found = FOOD_PLACE_NOT_FOUND;
    return 0;
}

int FoodGFO::check_if_placed() {
    if(FOOD_PLACED == this->placed) {
        return 1;
    } else return 0;
}

int FoodGFO::check_if_found() {
    if(FOOD_PLACE_FOUND == this->found) {
        return 1;
    } else return 0;
}

int FoodGFO::is_on_gf_yet(GameField& gf) {
    unsigned value;
    gf.getValueByCoordsXY(&value, this->XY);
    if(FOOD_GF_CODE == value) {
        return 1;
    }
    return 0;
}
