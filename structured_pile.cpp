#include "structured_pile.h"

#include <cstring>
#include <stdexcept>
#include <sstream>

using namespace std;

StructuredPile::StructuredPile(string name) : name(name) {
    memset(pile, 0, cards_size);
    sum = 0;
}

StructuredPile::~StructuredPile() {}

void StructuredPile::add_card(uint8_t id) {
    if (sum == LIMIT) {
        throw runtime_error("Pile is full");
    }
    
    sum++;
    pile[id]++;
}

void StructuredPile::remove_card(uint8_t id) {
    if (pile[id] == 0) {
        throw runtime_error("Card does not exist");
    }
    
    sum--;
    pile[id]--;
}

uint8_t StructuredPile::get_count(uint8_t id) {
    return pile[id];
}

uint8_t StructuredPile::operator[](uint8_t id) {
    return get_count(id);
}  

uint8_t StructuredPile::size() {
    return sum;
}

string StructuredPile::str() {
    stringstream ss;
    
    ss << name << ": ";
    
    for (unsigned i = 0; i < cards_size; i++) {
        if (pile[i] > 0) {
            ss << cards[i].str() << ": " << (unsigned) pile[i] << ", ";
        }
    }
    
    ss << "size: " << (unsigned) sum;
    
    return ss.str();
}
