#include <iostream>
#include "GameField.h"

using namespace std;

int GameField::initializeMatrix() {
    matrix = new unsigned*[this->sizeX];
    for(unsigned i = 0; i < this->sizeX; i++) {
        matrix[i] = new unsigned[this->sizeY];
        for(unsigned j = 0; j < this->sizeY; j++) {
            matrix[i][j] = 0;
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

GameField::~GameField() {
    for(unsigned i = 0; i < this->sizeX; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
    cout << "GameField destructor" << endl;
}
