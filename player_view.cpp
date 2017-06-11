#include "player_view.h"

PlayerView::PlayerView(uint8_t draw_pile_size, StructuredPile* discard_pile,
    Pile* forest, Pile* decay_pile,
    StructuredPile* display, HandStructuredPile* hand,
    StructuredPile* opponent_display, HandStructuredPile* opponent_hand) :
    draw_pile_size(draw_pile_size), discard_pile(discard_pile), forest(forest),
    decay_pile(decay_pile), display(display), hand(hand),
    opponent_display(opponent_display), opponent_hand(opponent_hand) {}

float* PlayerView::encode_for_nn() {
    float* encoded = new float[get_nn_encoding_size()];
    float* current = encoded;

    *current = draw_pile_size;
    current++;
    discard_pile->encode_for_nn_open(current);
    current += discard_pile->get_nn_open_encoding_size();
    forest->encode_for_nn(current);
    current += forest->get_nn_encoding_size();
    decay_pile->encode_for_nn(current);
    current += decay_pile->get_nn_encoding_size();
    display->encode_for_nn_open(current);
    current += display->get_nn_open_encoding_size();
    hand->encode_for_nn_open(current, display);
    current += hand->get_nn_open_encoding_size();
    opponent_display->encode_for_nn_open(current);
    current += opponent_display->get_nn_open_encoding_size();
    opponent_hand->encode_for_nn_closed(current, display);
    // current += opponent_hand->get_nn_closed_encoding_size();

    return encoded;
}

size_t PlayerView::get_nn_encoding_size() {
    return 1 + discard_pile->get_nn_open_encoding_size()
        + forest->get_nn_encoding_size() + decay_pile->get_nn_encoding_size()
        + display->get_nn_open_encoding_size() + hand->get_nn_open_encoding_size()
        + opponent_display->get_nn_open_encoding_size() + opponent_hand->get_nn_closed_encoding_size();
}
