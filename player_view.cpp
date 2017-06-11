#include "player_view.h"

PlayerView::PlayerView(uint8_t draw_pile_size, StructuredPile* discard_pile,
    Pile* forest, Pile* decay_pile,
    StructuredPile* display, HandStructuredPile* hand,
    StructuredPile* opponent_display, HandStructuredPile* opponent_hand) :
    draw_pile_size(draw_pile_size), discard_pile(discard_pile), forest(forest),
    decay_pile(decay_pile), display(display), hand(hand),
    opponent_display(opponent_display), opponent_hand(opponent_hand) {}

float* PlayerView::encode_for_nn() {
    float* params = new float[get_nn_encoding_size()];
    encode_for_nn(params);
    return params;
}

void PlayerView::encode_for_nn(float* params) {
    *params = draw_pile_size;
    params++;
    discard_pile->encode_for_nn_open(params);
    params += StructuredPile::get_nn_open_encoding_size();
    forest->encode_for_nn(params);
    params += forest->get_nn_encoding_size();
    decay_pile->encode_for_nn(params);
    params += decay_pile->get_nn_encoding_size();
    display->encode_for_nn_open(params);
    params += StructuredPile::get_nn_open_encoding_size();
    hand->encode_for_nn_open(params, display);
    params += HandStructuredPile::get_nn_open_encoding_size();
    opponent_display->encode_for_nn_open(params);
    params += StructuredPile::get_nn_open_encoding_size();
    opponent_hand->encode_for_nn_closed(params, display);
    // params += opponent_hand->get_nn_closed_encoding_size();
}

size_t PlayerView::get_nn_encoding_size() {
    return 1 + StructuredPile::get_nn_open_encoding_size()
        + Pile::get_nn_encoding_size(8) + Pile::get_nn_encoding_size(4)
        + StructuredPile::get_nn_open_encoding_size() + HandStructuredPile::get_nn_open_encoding_size()
        + StructuredPile::get_nn_open_encoding_size() + HandStructuredPile::get_nn_closed_encoding_size();
}
