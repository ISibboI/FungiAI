#include "hand_structured_pile.h"

#include <sstream>

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
    StructuredPile::add_card(id);
    
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
    
    ss << "Hand" << core << ", night_card_count: " << (unsigned) night_card_sum;
    
    return ss.str();
}
