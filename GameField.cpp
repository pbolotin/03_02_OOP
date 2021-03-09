#include <iostream>
#include "GameField.h"

using namespace std;

int GameField::initializeMatrix() {
    matrix = new unsigned*[this->sizeX];
    for(unsigned i = 0; i < this->sizeX; i++) {
        matrix[i] = new unsigned[this->sizeY];
        for(unsigned j = 0; j < this->sizeY; j++) {
            matrix[i][j] = EMPTY_GF_CODE;
        }
    }
    return 0;
}

GameField::GameField(): sizeX(10), sizeY(10) {
    initializeMatrix();
    //cout << "Constructor GameField::GameField()" << endl;
}

GameField::GameField(unsigned sizeX, unsigned sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    initializeMatrix();
    //cout << "Coustructor GameField::GameField(sizeX, sizeY)" << endl;
}

int GameField::getSizeXY(unsigned sizeXY[]) {
    sizeXY[0] = this->sizeX;
    sizeXY[1] = this->sizeY;
    return 0;
}

int GameField::getValueByCoordsXY(unsigned *value, Coords& coordsXY) {
    *value = matrix[coordsXY.getX()][coordsXY.getY()];
    return 0;
}

int GameField::setValueByCoordsXY(unsigned value, Coords &coordsXY) {
    if(coordsXY.getX() < this->sizeX && coordsXY.getY() < this->sizeY) {
        this->matrix[coordsXY.getX()][coordsXY.getY()] = value;
        return 0;
    }
    return -1;
}

GameField::~GameField() {
    for(unsigned i = 0; i < this->sizeX; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
    //cout << "GameField destructor" << endl;
}
