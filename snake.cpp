#include <iostream>
#include "GameField.h"
#include "Ticker.h"

using namespace std;

int main() {
    Ticker* ticker = new Ticker(1000000);
    int ret_val;
    while(1) {
        ret_val = ticker->do_tick();
        if(0 == ret_val) {
            cout << "tick ok" << endl;
        } else {
            cout << "tick wrong" << endl;
        }
    }
    return 0;
}
