#ifndef GAME_RUNNER_H
#define GAME_RUNNER_H

#include "game_state.h"
#include "action.h"

void run_game(GameState& game_state, int& result, Action* (&p1)(PlayerView*, GameState*),
    Action* (&p2)(PlayerView*, GameState*), void (&event_illegal_turn)(Action*));

#endif // GAME_RUNNER_H
