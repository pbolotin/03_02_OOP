#include "User.h"
#include <iostream>

using namespace std;

User::User(): the_last_will(USER_WANT_NOTHING) {
    cout << "Constructor of the User class" << endl;
}

void User::setLastWill(int last_will) {
    this->the_last_will = last_will;
}

int User::getLastWill() {
    return this->the_last_will;
}
