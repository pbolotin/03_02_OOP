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
    cout << "Constructor GameField::GameField()" << endl;
}

GameField::GameField(unsigned sizeX, unsigned sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    initializeMatrix();
    cout << "Coustructor GameField::GameField(sizeX, sizeY)" << endl;
}

int GameField::getSizeXY(unsigned sizeXY[]) {
    sizeXY[0] = this->sizeX;
    sizeXY[1] = this->sizeY;
    return 0;
}

int GameField::getValueByCoordsXY(unsigned *value, unsigned coordsXY[]) {
    *value = matrix[coordsXY[0]][coordsXY[1]];
    return 0;
}

int GameField::setValueByCoordsXY(unsigned value, unsigned coordsXY[]) {
    if(coordsXY[0] < this->sizeX && coordsXY[1] < this->sizeY) {
        this->matrix[coordsXY[0]][coordsXY[1]] = value;
        return 0;
    }
    return -1;
}

GameField::~GameField() {
    for(unsigned i = 0; i < this->sizeX; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
    cout << "GameField destructor" << endl;
}
