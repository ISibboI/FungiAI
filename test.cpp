#include "game_state.h"

#include <iostream>
#include <random>

using namespace std;

GameState* gs;
mt19937 r(526L);

void set_up() {
    cout << "sizeof(initial_draw_pile) = " << sizeof(initial_draw_pile) << endl;
    cout << "sizeof(Card) = " << sizeof(Card) << endl;
    cout << "sizeof(cards) = " << sizeof(cards) << endl;

    gs = new GameState(r);
}

void tear_down() {
    delete gs;
}

void test(void (&fun)()) {
    set_up();
    (*fun)();
    tear_down();
}

void test_set_up() {
    cout << gs->str();
}

int main() {
    test(test_set_up);

    return 0;
}
