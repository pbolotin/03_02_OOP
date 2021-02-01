#include <unistd.h>
#include "ConsoleSwitcher.h"

ConsoleSwitcher::ConsoleSwitcher() {}

int ConsoleSwitcher::storeCurrentTerminalState() {
    return 0;
}

int ConsoleSwitcher::setRawTerminalState() {
    return 0;
}

int ConsoleSwitcher::restoreTerminalState() {
    return 0;
}
