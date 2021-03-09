#include <iostream>
#include <cstdlib>
#include "GameProcess.h"
#include "GameRepresentator.h"
#include "Ticker.h"
#include "ConsoleSwitcher.h"

using namespace std;

int get_field_sizes_from_command_line(int argc, char* argv[], unsigned* sX, unsigned *sY) {
    int fnd_x = 0;
    int fnd_y = 0;
    char opt;
    while((opt = getopt(argc, argv, "x:y:")) != -1) {
        switch(opt) {
            case 'x':
                *sX = atoi(optarg);
                fnd_x = 1;
                break;
            case 'y':
                *sY = atoi(optarg);
                fnd_y = 1;
                break;
            default:
                return -1;
        }
    }
    if(fnd_x && fnd_y && *sY > 3 && *sY < 20 && *sX > 6 && *sX < 20) {
        return 0;
    }
    return -1;
}

int main(int argc, char* argv[]) {
    unsigned sizeX, sizeY;
    
    ConsoleSwitcher::storeCurrentTerminalState();
    ConsoleSwitcher::setNotCanonicalTerminalState();

    GameProcess *gp_ptr;
    if(-1 != get_field_sizes_from_command_line(argc, argv, &sizeX, &sizeY)) {
        gp_ptr = new GameProcess(sizeX, sizeY);
    } else {
        gp_ptr = new GameProcess();
    }
    GameProcess &gp = *gp_ptr;
    
    GameRepresentator gr;
    do {
        gp.doGamePause();
        gp.setUserWillByKey(ConsoleSwitcher::getLastKeyFromTerminal());
        gp.doGameProcessStep();
        ConsoleSwitcher::clearTerminalScreen();
        gr.outputGameFieldOnTerminal(gp.getGameField());
    } while(!gp.it_is_the_end());
    gp.doFinish();
    for(int j=0; j < 10; j++) {
        ConsoleSwitcher::clearTerminalScreen();
        gr.outputGameFieldOnTerminal(gp.getGameField());
        for(int i=0; i < 5; i++) {
            gp.doGamePause();
        }
        ConsoleSwitcher::clearTerminalScreen();
        gr.outputGameResultOnTerminal(gp.getGameField(), gp.getGameResult());
        for(int i=0; i < 10; i++) {
            gp.doGamePause();
        }
    }
    delete gp_ptr;
    ConsoleSwitcher::restoreTerminalState();
    return 0;
}
