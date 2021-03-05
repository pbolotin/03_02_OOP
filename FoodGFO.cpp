#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "FoodGFO.h"

using namespace std;

FoodGFO::FoodGFO(): XY(0,0), foundXY(0,0), eaten(FOOD_NOT_EATEN), placed(FOOD_NOT_PLACED), found(FOOD_PLACE_NOT_FOUND) {}

int FoodGFO::setOnGameField(GameField& gf) {
    unsigned XY[2];
    this->XY.getValueXY(XY[0],XY[1]);
    gf.setValueByCoordsXY(FOOD_GF_CODE, XY);
    this->placed = FOOD_PLACED;
    return 0;
}

int FoodGFO::removeFromGameField(GameField& gf) {
    unsigned sizeXY[2];
    gf.getSizeXY(sizeXY);
    
    unsigned coordsXY[2];
    for(unsigned i = 0; i < sizeXY[0]; i++) {
        coordsXY[0] = i;
        coordsXY[1] = 0;
        gf.setValueByCoordsXY(EMPTY_GF_CODE, coordsXY);
        coordsXY[1] = sizeXY[1]-1;
        gf.setValueByCoordsXY(EMPTY_GF_CODE, coordsXY);
    }
    return 0;
}

int FoodGFO::findCoordsForFood(GameField& gf, Coords& snakeHead) {
    vector<Coords*> good_places_for_food;
    unsigned sizeXY[2];
    unsigned coordsXY[2];
    unsigned headXY[2];
    unsigned value;
    gf.getSizeXY(sizeXY);
    
    for(unsigned i = 0; i < sizeXY[0]; i++) {
        for(unsigned j = 0; j < sizeXY[1]; j++) {
            coordsXY[0] = i;
            coordsXY[1] = j;
            gf.getValueByCoordsXY(&value, coordsXY);
            if(value == EMPTY_GF_CODE) {
                snakeHead.getValueXY(headXY[0], headXY[1]);
                if(abs((int)(coordsXY[0]-headXY[0])) + abs((int)(coordsXY[1]-headXY[1])) > 2) {
                    good_places_for_food.push_back(new Coords(coordsXY[0],coordsXY[1]));
                }
            }
        }
    }
    
    unsigned sz = good_places_for_food.size();
    if(sz != 0) {
        srand(time(nullptr));
        unsigned pos = rand() % sz;
        good_places_for_food[pos]->getValueXY(coordsXY[0], coordsXY[1]);
        this->foundXY.setValueXY(coordsXY[0], coordsXY[1]);
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
