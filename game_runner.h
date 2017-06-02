#ifndef GAME_RUNNER_H
#define GAME_RUNNER_H

#include "game_state.h"

struct action_descriptor {
    uint8_t action;
    uint8_t target;
    uint8_t count;
    uint8_t* drop_ids;
};

void run_game(GameState& game_state, int& result, action_descriptor (&p1)(uint8_t&, uint8_t*&,
    uint8_t*&, uint8_t*&, uint8_t&, uint8_t*&, uint8_t*&, uint8_t*&, uint8_t*&),
    action_descriptor (&p2)(uint8_t&, uint8_t*&,  uint8_t*&, uint8_t*&, uint8_t&, uint8_t*&,
    uint8_t*&, uint8_t*&, uint8_t*&));

#endif // GAME_RUNNER_H
