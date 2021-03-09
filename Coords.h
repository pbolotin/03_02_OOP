#ifndef _Coords_h_
#define _Coords_h_

#include <limits>

class Coords {
    unsigned   x;
    unsigned   y;
public:
    Coords();
    Coords(unsigned x, unsigned y);
    Coords(Coords& coords);
    Coords& operator=(Coords &) = default;
    int getValueXY(unsigned& x, unsigned& y);
    unsigned getX();
    unsigned getY();
    int setValueXY(unsigned x, unsigned y);
    int up();
    int down();
    int right();
    int left();
    ~Coords();
};

#endif

