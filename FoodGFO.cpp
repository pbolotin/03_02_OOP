#include <iostream>
#include <cstdlib>
#include <vector>
#include "FoodGFO.h"

using namespace std;

FoodGFO::FoodGFO(): XY(0,0), foundXY(0,0), eaten(0), placed(0) {}

int FoodGFO::setOnGameField(GameField& gf) {
    unsigned sizeXY[2];
    gf.getSizeXY(sizeXY);

    unsigned coordsXY[2];
    for(unsigned i = 0; i < sizeXY[0]; i++) {
        coordsXY[0] = i;
        coordsXY[1] = 0;
        gf.setValueByCoordsXY(FOOD_GF_CODE, coordsXY);
        coordsXY[1] = sizeXY[1]-1;
        gf.setValueByCoordsXY(FOOD_GF_CODE, coordsXY);
    }
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
    cout << good_places_for_food.size() << endl;
    Coords* good_place_ptr;
    
    while(!good_places_for_food.empty()) {
        good_place_ptr = good_places_for_food.back();
        good_places_for_food.pop_back();
        delete good_place_ptr;
    }
    return 0;
}
