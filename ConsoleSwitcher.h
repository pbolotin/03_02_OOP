#ifndef _ConsoleSwitcher_h_
#define _ConsoleSwitcher_h_

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum keys {
    KEY_s,
    KEY_S,
    KEY_l,
    KEY_L,
    KEY_q,
    KEY_Q,
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_F5,
    KEY_F6,
    UNKNOWN_KEY
};

#define READ_BUFFER_SIZE 1024

typedef struct seq_element {
    int code;
    long time;
} seq_element;

#define _HOW_MANY_CODES_SEQ 12

#define TIMEOUT_TO_NEW_KEY_NANOSEC 100000000

class ConsoleSwitcher {
private:
    ConsoleSwitcher();
    static struct termios myTermStruct;
    static char* _key_code_sequences[];

    static int _my_ncmp(char* s1, char* s2, int how_many);
    static int _rk_symbol_analysis(char* read_as_str);
    static int rk_readkey(enum keys *key);
    static int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);
public:
    static int storeCurrentTerminalState();
    static int setNotCanonicalTerminalState();
    static int clearTerminalScreen();
    static int restoreTerminalState();
    static enum keys getLastKeyFromTerminal();
};

#endif
