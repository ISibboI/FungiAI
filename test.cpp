#include "game_state.h"
#include "debug.h"

#include <iostream>
#include <random>

using namespace std;

mt19937 r(526L);
GameState gs(r);

void set_up() {
    gs = GameState(r);
}

void tear_down() {
}

void test(void (&fun)()) {
    set_up();
    (*fun)();
    tear_down();
}

void test_set_up() {
    cout << gs.str();
}

int main() {
    test(test_set_up);

    return 0;
}
