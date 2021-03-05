#include <iostream>
#include "Coords.h"

using namespace std;

Coords::Coords(): x(0), y(0) {}

Coords::Coords(unsigned x, unsigned y) {
    cout << "Constr: " << x << " " << y << endl;
    this->x = x;
    this->y = y;
}

int Coords::getValueXY(unsigned& x, unsigned& y) {
    x = this->x;
    y = this->y;
    return 0;
}

int Coords::setValueXY(unsigned x, unsigned y) {
    this->x = x;
    this->y = y;
    return 0;
}

Coords::~Coords() {
    cout << "Destr" << endl;
}
