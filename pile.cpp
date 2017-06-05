#include "pile.h"
#include "cards.h"

#include <stdexcept>
#include <sstream>
#include <cstring>

using namespace std;

Pile::Pile(uint8_t max_limit) {
    pile = new uint8_t[max_limit];
    memset(pile, 0, max_limit * sizeof(uint8_t));
    limit = 0;
    this->max_limit = max_limit;
}

Pile::~Pile() {
    delete[] pile;
}

void Pile::add_card(uint8_t id) {
    if (is_full()) {
        throw runtime_error("Cannot add card to full pile!");
    }
    
    pile[limit++] = id;
}

void Pile::clear() {
    limit = 0;
}

bool Pile::is_full() {
    return limit == max_limit;
}

void Pile::get_cards(uint8_t*& offset, uint8_t*& limit) {
    offset = pile;
    limit = pile + this->limit;
}

uint8_t* Pile::get_offset() {
    return pile;
}

uint8_t* Pile::get_limit() {
    return pile + limit;
}

uint8_t Pile::size() {
    return limit;
}

string Pile::str() {
    stringstream ss;
    
    for (unsigned i = 0; i < limit; i++) {
        ss << cards[pile[i]].str();
        
        if (i + 1 < limit) {
            ss << ", ";
        }
    }
    
    return ss.str();
}
