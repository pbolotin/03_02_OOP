#include <unistd.h>
#include <iostream>
#include "ConsoleSwitcher.h"
#include "User.h"

using namespace std;

/*Private*/
struct termios ConsoleSwitcher::myTermStruct;

char* ConsoleSwitcher::_key_code_sequences[_HOW_MANY_CODES_SEQ] = {
        (char*)"\163",//s
        (char*)"\123",//S
        (char*)"\154",//l
        (char*)"\114",//L
        (char*)"\161",//q
        (char*)"\121",//Q
        (char*)"\033\133\101",//KEY_UP
        (char*)"\033\133\102",//KEY_DOWN
        (char*)"\033\133\103",//KEY_RIGHT
        (char*)"\033\133\104",//KEY_LEFT
        (char*)"\033\133\061\065\176",//KEY_F5
        (char*)"\033\133\061\067\176"//KEY_F6
};

int ConsoleSwitcher::_my_ncmp(char* s1, char* s2, int how_many) {
    for(int i = 0; i < how_many; i++) {
        //printf("%dcmp %d %d\n", i, s1[i], s2[i]);
        if(s1[i] != s2[i]) {
            return -1;
        }
    }
    return 0;
}

int ConsoleSwitcher::_rk_symbol_analysis(char* read_as_str) {
    //printf("Do analysis\n");
    int ncmp_result;
    for(int i = 0; i < _HOW_MANY_CODES_SEQ; i++) {
        ncmp_result = _my_ncmp(_key_code_sequences[i], read_as_str, strlen(_key_code_sequences[i]));
        //printf("Cmp res %d\n", ncmp_result);
        if(ncmp_result == 0) {
            //printf("Match!\n");
            return i;
        }
    }
    return -1;
}

int ConsoleSwitcher::rk_readkey(enum keys *key) {
    //time_t   tv_sec;        /* seconds */
    //long     tv_nsec;       /* nanoseconds */
    struct timespec ts;
    //clock_gettime(CLOCK_REALTIME, &ts);
    
    int fd = 0;//stdin
    /*Check if fd is a tty*/
    if(!isatty(fd)) {
        perror("Sorry, need to use termian as stdin 0\n");
        return -1;
    }
    char for_read;
    int read_res;
    long new_time;
    seq_element read_buffer[READ_BUFFER_SIZE];
    char read_char_seq[READ_BUFFER_SIZE];
    int counter = 0;
    int analysis_res = -1;
    while(1) {
        read_res = read(0, &for_read, sizeof(for_read));
        clock_gettime(CLOCK_REALTIME, &ts);
        new_time = ts.tv_sec*1000000000 + ts.tv_nsec;
        /*Check if timeout is*/
        if(counter > 0) {
            long diff_time = new_time - read_buffer[counter - 1].time;
            if(diff_time > TIMEOUT_TO_NEW_KEY_NANOSEC) {
                counter = 0;
                *key = UNKNOWN_KEY;
                break;
            }
        }
        if(0 == read_res) {
            //printf("\nNo input anymore\n");
            break;
        } else if(read_res < 0) {
            perror("\nError occured when reading\n");
            return -1;
        }
        read_buffer[counter].code = for_read;
        read_buffer[counter].time = new_time;
        read_char_seq[counter] = for_read;
        read_char_seq[counter+1] = 0;
        //printf("Was read: %o at %ld\n", (int)for_read, read_buffer[counter].time);
        analysis_res = _rk_symbol_analysis(read_char_seq);
        if(analysis_res >= 0) {
            /*CAUTON! ERROR WARNING, NEED TO HAVE THE SAME INDEXES IN KEY ENUM AND SEQ ARRAY*/
            *key = (enum keys)analysis_res;
            return 1;
        }
        counter++;
    }
    return 0;
}

int ConsoleSwitcher::rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)  {
    /*
    struct termios{
        tcflag_t c_iflag;
        tcflag_t c_oflag;
        tcflag_t c_lflag;
        tcflag_t c_cflag;
        tcflag_t c_cc[NCCS];
    }*/
    struct termios myTermStruct;
    /*Load old termios value*/
    tcgetattr(0, &myTermStruct);
    
    if(regime & ICANON) {
        printf("Set ICANON flag\n");
        myTermStruct.c_lflag |= ICANON;
    } else {
        if(vtime < 0 || vmin < 0) {
            perror("Error, vtime or vmin are incorrect\n");
            return -1;
        }
        printf("Unset ICANON flag\n");
        myTermStruct.c_lflag &= ~ICANON;
            /*
        MIN == 0, TIME == 0 (polling read)
        If data is available, read(2) returns immediately,
        with the lesser of the number of bytes available,
        or the number of bytes requested.
        If no data is available, read(2) returns 0.
        */
        if(vmin == 0 && vtime == 0) {
            printf("Set polling read\n");
            myTermStruct.c_cc[VMIN] = vmin;
            myTermStruct.c_cc[VTIME] = vtime;
        }
        /*
        MIN > 0, TIME == 0 (blocking read)
        read(2) blocks until MIN bytes are available,
        and returns up to the number of bytes requested.
        */
        else if(vmin > 0 && vtime == 0) {
            printf("Set blocking read\n");
            myTermStruct.c_cc[VMIN] = vmin;
            myTermStruct.c_cc[VTIME] = vtime;
        }
        /*
        MIN == 0, TIME > 0 (read with timeout)
        TIME specifies the limit for a timer in tenths of a second.
        The timer is started when read(2) is called.
        read(2) returns either when at least one byte of data is available,
        or when the timer expires.
        If the timer expires without any input becoming available,
        read(2) returns 0.  If data is already available
        at the time of the call to read(2),
        the call behaves as though the data was received immediately after the call.
        */ 
        else if(vmin == 0 && vtime > 0) {
            printf("Set read with timeout\n");
            myTermStruct.c_cc[VMIN] = vmin;
            myTermStruct.c_cc[VTIME] = vtime;
        }
        /* MIN > 0, TIME > 0 (read with interbyte timeout)
        TIME specifies the limit for a timer in tenths of a second.
        Once an initial byte of input becomes available,
        the timer is restarted after each further byte is received.
        read(2) returns when any of the following conditions is met:
        MIN bytes have been received.
        The interbyte timer expires.
        The number of bytes requested by read(2) has been received.
        (POSIX does not specify this termination condition,
        and on some other implementations read(2) does not return in this case.)
        Because the timer is started only after the initial byte becomes available,
        at least one byte will be read.
        If data is already available at the time of the call to read(2),
        the call behaves as though the data was received immediately after the call.
        */
        else if(vmin > 0 && vtime > 0) {
            printf("Set read with interbyte timeout\n");
            myTermStruct.c_cc[VMIN] = vmin;
            myTermStruct.c_cc[VTIME] = vtime;
        }
    }
    if(echo & ECHO) {
        printf("Set ECHO flag\n");
        myTermStruct.c_lflag |= ECHO;
    } else {
        printf("Unset ECHO flag\n");
        myTermStruct.c_lflag &= ~ECHO;
    }
    if(sigint & ISIG) {
        printf("Set ISIG flag\n");
        myTermStruct.c_lflag |= ISIG;
    } else {
        printf("Unset ISIG flag\n");
        myTermStruct.c_lflag &= ~ISIG;
    }
    /*Set new value of termios*/
    tcsetattr(0, TCSADRAIN, &myTermStruct);
    return 0;
}

/*Public*/
ConsoleSwitcher::ConsoleSwitcher() {}

int ConsoleSwitcher::storeCurrentTerminalState() {
    tcgetattr(0, &ConsoleSwitcher::myTermStruct);
    return 0;
}

int ConsoleSwitcher::setNotCanonicalTerminalState() {
    ConsoleSwitcher::rk_mytermregime(~ICANON, 0, 0, 0, ISIG);
    return 0;
}

int ConsoleSwitcher::restoreTerminalState() {
    tcsetattr(0, TCSADRAIN, &ConsoleSwitcher::myTermStruct);
    return 0;
}

enum keys ConsoleSwitcher::getLastKeyFromTerminal() {
    enum keys key = UNKNOWN_KEY;
    enum keys lastKey = UNKNOWN_KEY;
    int ret_val;
    do {
        lastKey = key;
        ret_val = ConsoleSwitcher::rk_readkey(&key);
    } while(ret_val);
    //cout << "ConsoleSwitcher::getKeyFromTerminal" << ret_val << lastKey << endl;
    return lastKey;
}
