#include "hand_structured_pile.h"
#include "nn_encoding.h"

#include <sstream>
#include <stdexcept>

using namespace std;

HandStructuredPile::HandStructuredPile(string name) : StructuredPile(name) {
    night_card_sum = 0;
}

HandStructuredPile::~HandStructuredPile() {}

void HandStructuredPile::add_card(uint8_t id) {
    StructuredPile::add_card(id);

    if (id >= night_min_id && id <= night_max_id) {
        night_card_sum++;
    }
}

void HandStructuredPile::add_cards(uint8_t id, uint8_t count) {
    StructuredPile::add_cards(id, count);

    if (id >= night_min_id && id <= night_max_id) {
        night_card_sum += count;
    }
}

void HandStructuredPile::remove_card(uint8_t id) {
    StructuredPile::remove_card(id);

    if (id >= night_min_id && id <= night_max_id) {
        night_card_sum--;
    }
}

void HandStructuredPile::remove_cards(uint8_t id, uint8_t count) {
    StructuredPile::remove_cards(id, count);

    if (id >= night_min_id && id <= night_max_id) {
        night_card_sum -= count;
    }
}

uint8_t HandStructuredPile::get_night_card_count() {
    return night_card_sum;
}

string HandStructuredPile::str() {
    string core = StructuredPile::str();
    stringstream ss;

    ss << core << ", night_card_count: " << (unsigned) night_card_sum;

    return ss.str();
}

int8_t HandStructuredPile::get_remaining_capacity(StructuredPile* display) {
    return 8 + display->get_count(basket) - size() - (display->get_count(fly_agaric) > 0 ? 4 : 0);
}

uint8_t HandStructuredPile::get_effective_shroom_count(uint8_t id) {
    if (id >= night_min_id) {
        throw runtime_error("Id is not a basic shroom");
    }

    return get_count(id) + (id != 8 ? get_count(id + 9) * 2 : 0);
}

void HandStructuredPile::encode_for_nn_open(float* params, StructuredPile* display) {
    for (unsigned card = 0; card < special_min_id; card++) {
        uint8_t count = get_count(card);
        params = nn_encode_int_unary(params, count, cards_max[card]);
    }

    params = nn_encode_int_unary(params, get_remaining_capacity(display), 18);
}

void HandStructuredPile::encode_for_nn_open(float* params) {
    throw runtime_error("Deleted function");
}

size_t HandStructuredPile::get_nn_open_encoding_size() {
    return cards_max_sum - cards_max[moon] - cards_max[basket] - cards_max[fly_agaric] - cards_max[stick]
        + 18; // Max hand capacity
}

void HandStructuredPile::encode_for_nn_closed(float* params, StructuredPile* display) {
    for (unsigned card = 0; card < special_min_id; card++) {
        if (card >= night_min_id && card <= night_max_id) {
            continue;
        }

        params = nn_encode_int_unary(params, get_count(card), cards_max[card]);
    }

    params = nn_encode_int_unary(params, get_night_card_count(), cards_max[moon]);
    params = nn_encode_int_unary(params, get_remaining_capacity(display), 18);
}

size_t HandStructuredPile::get_nn_closed_encoding_size() {
    return cards_max_sum - cards_max[moon] - cards_max[basket] - cards_max[fly_agaric] - cards_max[stick]
        + 18; // Max hand capacity
}
