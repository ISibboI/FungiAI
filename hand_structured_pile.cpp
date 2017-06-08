#include "hand_structured_pile.h"

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

void HandStructuredPile::remove_card(uint8_t id) {
    StructuredPile::remove_card(id);

    if (id >= night_min_id && id <= night_max_id) {
        night_card_sum--;
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

int8_t HandStructuredPile::get_remaining_capacity(StructuredPile& display) {
    return 8 + display[basket] - size() - (display[fly_agaric] > 0 ? 4 : 0);
}

uint8_t HandStructuredPile::get_effective_shroom_count(uint8_t id) {
    if (id >= night_min_id) {
        throw runtime_error("Id is not a basic shroom");
    }

    return get_count(id) + (id != 8 ? get_count(id + 9) : 0);
}
