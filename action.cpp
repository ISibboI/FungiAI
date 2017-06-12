#include "action.h"
#include "nn_encoding.h"

#include <sstream>
#include <stdexcept>

using namespace std;

Action::Action(uint8_t id, uint8_t target, uint8_t count, StructuredPile* drop_ids,
    StructuredPile* display, HandStructuredPile* hand) : id(id), target(target),
    count(count), drop_ids(drop_ids), display(display), hand(hand) {}

Action::Action(uint8_t id, uint8_t target, StructuredPile* drop_ids,
    StructuredPile* display, HandStructuredPile* hand) : id(id), target(target),
    drop_ids(drop_ids), display(display), hand(hand) {

    count = 0;
}

Action::Action(uint8_t id, StructuredPile* drop_ids,
    StructuredPile* display, HandStructuredPile* hand) : id(id),
    drop_ids(drop_ids), display(display), hand(hand) {

    target = 0;
    count = 0;
}

Action::Action(uint8_t id, uint8_t target, uint8_t count,
    StructuredPile* display, HandStructuredPile* hand) : id(id), target(target),
    count(count), display(display), hand(hand) {

    drop_ids = 0;
}

Action::Action(uint8_t id, StructuredPile* display, HandStructuredPile* hand) : id(id),
    display(display), hand(hand) {

    target = 0;
    count = 0;
    drop_ids = 0;
}

Action::Action() {
    id = 0;
    target = 0;
    count = 0;
    drop_ids = 0;
    display = 0;
    hand = 0;
}

Action::~Action() {
    if (drop_ids != 0) {
        delete drop_ids;
    }
}

string Action::str() {
    stringstream ss;

    switch (id) {
    case 1:
        ss << "Pick(" << (unsigned) target << ", " << drop_ids->str() << ")";
        break;
    case 2:
        ss << "PickDecay(" << drop_ids->str() << ")";
        break;
    case 3:
        ss << "Cook(" << cards[target].str() << ", " << (unsigned) count << ")";
        break;
    case 4:
        ss << "Sell(" << cards[target].str() << ", " << (unsigned) count << ")";
        break;
    case 5:
        return "PlayPan";
    case 6:
        return "Pass";
    default:
        throw runtime_error("Unknown action id");
    }

    return ss.str();
}

Action::Action(float* params, StructuredPile* display, HandStructuredPile* hand) :
    display(display), hand(hand) {

    id = nn_decode_int_one_of_n(&params, 6) + 1;
    target = nn_decode_int_one_of_n(&params, target_size[id - 1]);
    params += night_min_id - target_size[id - 1];
    count = nn_decode_int_one_of_n(&params, 10) + 2;
    drop_ids = nn_decode_drop_ids(&params);
}

size_t Action::get_nn_decoding_size() {
    return cards_size + 6 /*id*/ + night_min_id /*target*/ + 10 /*count*/ + 4 * (special_min_id + 1) /*drop_ids*/;
}
