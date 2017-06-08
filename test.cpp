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
    // cout << "Illegal turn: " << (unsigned) action.action << endl;
    #endif // DEBUG
}

action_descriptor get_random_turn(PlayerView& player_view) {

    uniform_int_distribution<uint8_t> d6(1, 6);
    uniform_int_distribution<uint8_t> d8(0, 7);
    uniform_int_distribution<uint8_t> d9(0, 8);
    action_descriptor action;
    action.action = d6(r);

    switch (action.action) {
    case 1:
        action.target = d8(r);
    case 2:
        break;
    case 3:
    case 4:
        action.target = d9(r);
        action.count = (*player_view.hand)[action.target];
        break;
    case 5:
    case 6:
        break;
    default:
        throw runtime_error("Illegal action");
    }

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
