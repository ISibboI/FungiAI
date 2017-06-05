#ifndef GAME_RUNNER_H
#define GAME_RUNNER_H

#include "game_state.h"
#include "structured_pile.h"

#include <string>

class action_descriptor {
public:
    action_descriptor();
    ~action_descriptor();

    uint8_t action;
    uint8_t target;
    uint8_t count;
    StructuredPile drop_ids;

    std::string str();
};

void run_game(GameState& game_state, int& result, action_descriptor (&p1)(uint8_t&, StructuredPile*&,
    Pile*&, Pile*&, StructuredPile*&, HandStructuredPile*&, StructuredPile*&, HandStructuredPile*&),
    action_descriptor (&p2)(uint8_t&, StructuredPile*&,  Pile*&, Pile*&, StructuredPile*&,
    HandStructuredPile*&, StructuredPile*&, HandStructuredPile*&), void (&event_illegal_turn)(action_descriptor&));

#endif // GAME_RUNNER_H
