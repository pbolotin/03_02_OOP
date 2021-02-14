#include <iostream>
#include "GameProcess.h"
#include "GameRepresentator.h"
#include "Ticker.h"
#include "ConsoleSwitcher.h"

using namespace std;

int main() {
    Ticker* ticker = new Ticker(100000);
    int ret_val;
    int i = 0;
    ConsoleSwitcher::storeCurrentTerminalState();
    ConsoleSwitcher::setNotCanonicalTerminalState();
    GameProcess gp;
    GameRepresentator gr;
    while(!gp.it_is_the_end()) {
        ret_val = ticker->do_tick();
        if(0 == ret_val) {
            cout << "tick ok" << endl;
        } else {
            cout << "tick wrong" << endl;
        }
        i++;
        gp.setUserWillByKey(ConsoleSwitcher::getLastKeyFromTerminal());
        gp.doGameProcessStep();
    }
    ConsoleSwitcher::restoreTerminalState();
    return 0;
}
