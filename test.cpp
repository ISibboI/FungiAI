#include "game_state.h"
#include "debug.h"
#include "game_runner.h"

#include <iostream>
#include <random>
#include <stdexcept>

using namespace std;

#define ensure(x) if (!x) {cout << "Test error! " << #x << endl;};

mt19937 r(526L);
GameState* gs;

void set_up() {
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
    cout << gs->str() << endl;
}

void event_illegal_turn(action_descriptor& action) {
    #ifdef DEBUG
    cout << "Illegal turn: " << (unsigned) action.action << endl;
    #endif // DEBUG
}

action_descriptor get_random_turn(uint8_t& draw_pointer, uint8_t*& discard_pile,
    uint8_t*& forest, Pile*& decay_pile,
    uint8_t*& display, uint8_t*& hand,
    uint8_t*& opponent_display, uint8_t*& opponent_hand) {

    print("Entering get random turn");
    uniform_int_distribution<uint8_t> d6(1, 6);
    uniform_int_distribution<uint8_t> d8(0, 7);
    uniform_int_distribution<uint8_t> d19(0, 18);
    action_descriptor action;
    print("Completing action 1");
    action.action = d6(r);
    action.drop_ids = 0;

    print("Completing action 2");

    switch (action.action) {
    case 1:
        action.target = d8(r);
    case 2:
        action.drop_ids = new uint8_t[1];
        action.drop_ids[0] = n1;
        break;
    case 3:
    case 4:
        action.target = d19(r);
        action.count = hand[action.target];
        break;
    case 5:
    case 6:
        break;
    default:
        throw runtime_error("Illegal action");
    }

    print("Exiting get random turn");
    return action;
}

void test_stupid_game() {
    int result;
    run_game(*gs, result, get_random_turn, get_random_turn, event_illegal_turn);
    cout << "Result is " << result << endl;
}

int main() {
    test(test_set_up);
    test(test_stupid_game);

    return 0;
}
