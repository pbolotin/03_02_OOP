#ifndef _Coords_h_
#define _Coords_h_

class Coords {
    unsigned   x;
    unsigned   y;
public:
    Coords();
    Coords(unsigned x, unsigned y);
    int getValueXY(unsigned& x, unsigned& y);
    int setValueXY(unsigned x, unsigned y);
    ~Coords();
};

#endif

