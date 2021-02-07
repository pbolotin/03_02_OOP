#ifndef _User_h_
#define _User_h_

#define USER_WANT_NOTHING     0
#define USER_WANT_SNAKE_UP    1
#define USER_WANT_SNAKE_DOWN  2
#define USER_WANT_SNAKE_LEFT  3
#define USER_WANT_SNAKE_RIGHT 4
#define USER_WANT_GAME_QUIT   10
#define USER_WANT_GAME_PAUSE  11

class User {
private:
    int the_last_will;
public:
    User();
    void setLastWill(int last_will);
    int getLastWill();
};

#endif
