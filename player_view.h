#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include "structured_pile.h"
#include "pile.h"
#include "hand_structured_pile.h"

class PlayerView {
public:
    PlayerView(uint8_t draw_pile_size, StructuredPile* discard_pile,
        Pile* forest, Pile* decay_pile,
        StructuredPile* display, HandStructuredPile* hand,
        StructuredPile* opponent_display, HandStructuredPile* opponent_hand);

    const uint8_t draw_pile_size;
    StructuredPile* const discard_pile;
    Pile* const forest;
    Pile* const decay_pile;
    StructuredPile* const display;
    HandStructuredPile* const hand;
    StructuredPile* const opponent_display;
    HandStructuredPile* const opponent_hand;
};

#endif // PLAYER_VIEW_H
