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
    gp.doFinish();
    for(int j=0; j < 10; j++) {
        gr.outputGameFieldOnTerminal(gp.getGameField());
        for(int i=0; i < 5; i++) {
            gp.doGamePause();
        }
        gr.outputGameResultOnTerminal(gp.getGameField(), gp.getGameResult());
        for(int i=0; i < 10; i++) {
            gp.doGamePause();
        }
    }
    ConsoleSwitcher::restoreTerminalState();
    return 0;
}
