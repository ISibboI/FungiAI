#include "player_view.h"

PlayerView::PlayerView(uint8_t draw_pile_size, StructuredPile* discard_pile,
    Pile* forest, Pile* decay_pile,
    StructuredPile* display, HandStructuredPile* hand,
    StructuredPile* opponent_display, HandStructuredPile* opponent_hand) :
    draw_pile_size(draw_pile_size), discard_pile(discard_pile), forest(forest),
    decay_pile(decay_pile), display(display), hand(hand),
    opponent_display(opponent_display), opponent_hand(opponent_hand) {}
