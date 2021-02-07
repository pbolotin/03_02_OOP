#include <iostream>
#include "GameProcess.h"
#include "GameRepresentator.h"
#include "Ticker.h"
#include "ConsoleSwitcher.h"

using namespace std;

int main() {
    Ticker* ticker = new Ticker(1000000);
    int ret_val;
    int i = 0;
    ConsoleSwitcher::storeCurrentTerminalState();
    ConsoleSwitcher::setNotCanonicalTerminalState();
    GameProcess gp;
    GameRepresentator gr;
    while(i < 10) {
        ret_val = ticker->do_tick();
        if(0 == ret_val) {
            cout << "tick ok" << endl;
        } else {
            cout << "tick wrong" << endl;
        }
        i++;
    }
    ConsoleSwitcher::restoreTerminalState();
    return 0;
}
