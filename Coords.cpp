#include <iostream>
#include "Coords.h"

using namespace std;

Coords::Coords(): x(0), y(0) {}

Coords::Coords(unsigned x, unsigned y) {
    //cout << "Constr: " << x << " " << y << endl;
    this->x = x;
    this->y = y;
}

Coords::Coords(Coords& coords) {
    //cout << "Constr: " << x << " " << y << endl;
    this->x = coords.getX();
    this->y = coords.getY();
}

int Coords::getValueXY(unsigned& x, unsigned& y) {
    x = this->x;
    y = this->y;
    return 0;
}

unsigned Coords::getX() {
    return this->x;
}

unsigned Coords::getY() {
    return this->y;
}

int Coords::setValueXY(unsigned x, unsigned y) {
    this->x = x;
    this->y = y;
    return 0;
}

int Coords::up() {
    if(this->y > 0)
        this->y -= 1;
    else return -1;
    return 0;
}

int Coords::down() {
    if(this->y < numeric_limits<unsigned int>::max())
        this->y += 1;
    else return -1;
    return 0;
}

int Coords::right() {
    if(this->x < numeric_limits<unsigned int>::max())
        this->x += 1;
    else return -1;
    return 0;
}

int Coords::left() {
    if(this->x > 0)
        this->x -= 1;
    else return -1;
    return 0;
}

Coords::~Coords() {
    //cout << "Destr" << endl;
}
