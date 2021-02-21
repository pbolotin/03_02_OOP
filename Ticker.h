#ifndef _Ticker_h_
#define _Ticker_h_

class Ticker {
private:
    unsigned long tick_length;
    unsigned long tick_counter;
public:
    Ticker();
    Ticker(unsigned long tick_length);
    Ticker(unsigned long tick_length, unsigned long tick_counter);
    int do_tick();
    unsigned long getTickCount();
};

#endif
