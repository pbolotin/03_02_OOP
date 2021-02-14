#include <iostream>
#include "WallGFO.h"

using namespace std;

int WallGFO::placeOnGameField(GameField& gf) {
    unsigned sizeXY[2];
    gf.getSizeXY(sizeXY);
    cout << "WallGFO see GameField sizeXY:" << sizeXY[0] << " " << sizeXY[1] << endl;
    return 0;
}
