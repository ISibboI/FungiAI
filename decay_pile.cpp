#include "decay_pile.h"

#include <stdexcept>
#include <cstdint>
#include <sstream>
#include <cstring>

using namespace std;

DecayPile::DecayPile() {
    memset(pile, 0, sizeof(pile));
    limit = 0;
}

DecayPile::~DecayPile() {
}

void DecayPile::add_card(uint8_t id) {
    if (is_full()) {
        throw runtime_error("Cannot add card to full decay pile!");
    }
    
    pile[limit++] = id;
}

void DecayPile::clear() {
    limit = 0;
}

bool DecayPile::is_full() {
    return limit == SIZE;
}

void DecayPile::get_cards(uint8_t*& offset, uint8_t*& limit) {
    offset = pile;
    limit = pile + this->limit;
}

uint8_t* DecayPile::get_offset() {
    return pile;
}

uint8_t* DecayPile::get_limit() {
    return pile + limit;
}

uint8_t DecayPile::size() {
    return limit;
}

int8_t DecayPile::net_size() {
    int8_t result = 0;
    
    for (unsigned i = 0; i < limit; i++) {
        if (pile[i] == basket) {
            result -= 2;
        } else if (pile[i] < special_min_id) {
            result++;
        }
    }
    
    return result;
}

string DecayPile::str() {
    stringstream ss;
    
    ss << "Decay pile: ";
    
    for (unsigned i = 0; i < limit; i++) {
        ss << cards[pile[i]].str();
        
        if (i + 1 < limit) {
            ss << ", ";
        }
    }
    
    return ss.str();
}
