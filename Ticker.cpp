#include <unistd.h>
#include "Ticker.h"

Ticker::Ticker(): tick_length(1000), tick_counter(0) {}

Ticker::Ticker(unsigned long tick_length): tick_counter(0) {
    this->tick_length = tick_length;
}

Ticker::Ticker(unsigned long tick_length, unsigned long tick_counter) {
    this->tick_length = tick_length;
    this->tick_counter = tick_counter;
}

int Ticker::do_tick() {
    int ret_val = usleep(this->tick_length);
    if(0 != ret_val) {
        return ret_val;
    }
    this->tick_counter++;
    return 0;
}
