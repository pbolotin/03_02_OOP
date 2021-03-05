#include <iostream>
#include "GameProcess.h"
#include "GameRepresentator.h"
#include "Ticker.h"
#include "ConsoleSwitcher.h"

using namespace std;

int main() {
    ConsoleSwitcher::storeCurrentTerminalState();
    ConsoleSwitcher::setNotCanonicalTerminalState();
    GameProcess gp;
    GameRepresentator gr;
    do {
        gp.doGamePause();
        gp.setUserWillByKey(ConsoleSwitcher::getLastKeyFromTerminal());
        gp.doGameProcessStep();
        gr.outputGameFieldOnTerminal(gp.getGameField());
    } while(!gp.it_is_the_end());
    ConsoleSwitcher::restoreTerminalState();
    return 0;
}
