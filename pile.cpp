#include "pile.h"
#include "cards.h"

#include <stdexcept>
#include <sstream>
#include <cstring>

using namespace std;

Pile::Pile(string name, uint8_t max_limit) {
    pile = new uint8_t[max_limit];
    memset(pile, 0, max_limit * sizeof(uint8_t));
    limit = 0;
    this->max_limit = max_limit;
    this->name = name;
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

uint8_t Pile::remove_card(uint8_t index) {
    if (index >= size()) {
        throw runtime_error("Remove index out of bounds");
    }

    uint8_t result = pile[index];
    limit--;
    
    for (unsigned i = index; i < limit; i++) {
        pile[i] = pile[i + 1];
    }
    
    return result;
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

int8_t Pile::pick_all_size() {
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

string Pile::str() {
    stringstream ss;
    
    ss << name << ": ";
    
    for (unsigned i = 0; i < limit; i++) {
        ss << cards[pile[i]].str();
        
        if (i + 1 < limit) {
            ss << ", ";
        }
    }
    
    return ss.str();
}

uint8_t Pile::operator[](uint8_t index) {
    if (index >= size()) {
        throw runtime_error("Index out of bounds");
    }
    
    return pile[index];
}
