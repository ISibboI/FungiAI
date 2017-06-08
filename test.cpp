#include "game_state.h"
#include "debug.h"
#include "game_runner.h"
#include "action.h"

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

void event_illegal_turn(Action* action) {
    #ifdef DEBUG
    // cout << "Illegal turn: " << (unsigned) action.action << endl;
    #endif // DEBUG
}

Action* get_random_turn(PlayerView* player_view, GameState* game_state) {
    vector<Action*> actions = game_state->generate_actions(player_view->display, player_view->hand);
    uniform_int_distribution<> choice(0, actions.size() - 1);
    size_t chosen_index = choice(r);

    for (size_t i = 0; i < chosen_index; i++) {
        delete actions[i];
    }

    for (size_t i = chosen_index + 1; i < actions.size(); i++) {
        delete actions[i];
    }

    return actions[chosen_index];
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
