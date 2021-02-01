#ifndef _ConsoleSwitcher_h_
#define _ConsoleSwitcher_h_

#include <termios.h>

class ConsoleSwitcher {
private:
    struct termios myTermStruct;
public:
    ConsoleSwitcher();
    int storeCurrentTerminalState();
    int setRawTerminalState();
    int restoreTerminalState();
};

#endif
