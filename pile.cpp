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

void Pile::add_cards(const uint8_t* ids, uint8_t length) {
    if (limit + length < limit || limit + length > max_limit) {
        throw runtime_error("Not enough space");
    }

    memcpy(pile + limit, ids, length);
    limit += length;
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

uint8_t Pile::remove_last_card() {
    return remove_card(size() - 1);
}

void Pile::remove_cards(uint8_t index, uint8_t length, uint8_t* destination) {
    if (index + length < index || index + length > limit) {
        throw runtime_error("Remove range out of bounds");
    }

    memcpy(destination, pile + index, length);
    limit -= length;

    for (unsigned i = index; i < limit; i++) {
        pile[i] = pile[i + length];
    }
}

void Pile::make_space(uint8_t length) {
    if (limit + length < limit || limit + length > max_limit) {
        throw runtime_error("Not enough space");
    }

    limit += length;
}

void Pile::clear() {
    limit = 0;
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

uint8_t Pile::operator[](uint8_t index) {
    if (index >= size()) {
        throw runtime_error("Index out of bounds");
    }

    return pile[index];
}

uint8_t Pile::size() {
    return limit;
}

bool Pile::is_full() {
    return limit == max_limit;
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

StructuredPile* Pile::structurize() {
    StructuredPile* result = new StructuredPile(name);

    for (uint8_t* i = get_offset(); i < get_limit(); i++) {
        result->add_card(*i);
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
