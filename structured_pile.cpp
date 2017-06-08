#include "structured_pile.h"

#include <cstring>
#include <stdexcept>
#include <sstream>

using namespace std;

StructuredPile::StructuredPile(string name) : name(name) {
    memset(pile, 0, cards_size);
    sum = 0;
    size_sum = 0;
}

StructuredPile::~StructuredPile() {}

void StructuredPile::add_card(uint8_t id) {
    if (sum == LIMIT) {
        throw runtime_error("Pile is full");
    }

    sum++;
    size_sum += cards[id].size;
    pile[id]++;
}

void StructuredPile::add_cards(uint8_t id, uint8_t count) {
    if (sum + count > LIMIT || sum + count < sum) {
        throw runtime_error("Not enough space");
    }

    sum += count;
    size_sum += cards[id].size * count;
    pile[id] += count;
}

void StructuredPile::remove_card(uint8_t id) {
    if (pile[id] == 0) {
        throw runtime_error("Card does not exist");
    }

    sum--;
    size_sum -= cards[id].size;
    pile[id]--;
}

void StructuredPile::remove_cards(uint8_t id, uint8_t count) {
    if (pile[id] - count < 0 || pile[id] - count > pile[id]) {
        throw runtime_error("Not enough cards");
    }

    sum -= count;
    size_sum -= cards[id].size * count;
    pile[id] -= count;
}

void StructuredPile::set_cards(uint8_t id, uint8_t count) {
    uint8_t current = (*this)[id];

    if (count > current) {
        add_cards(id, count - current);
    } else {
        remove_cards(id, current - count);
    }
}

bool StructuredPile::remove_shrooms_maximizing_space(uint8_t id, uint8_t count) {
    if (pile[id] >= count) {
        remove_cards(id, count);
        return false;
    } else {
        if (id <= lower_pair_shroom_max_id) {
            remove_card(id + to_night_card);
            remove_cards(id, count - 2);
            return true;
        } else {
            throw runtime_error("Not enough cards");
        }
    }
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

int8_t StructuredPile::pick_all_size() {
    return size_sum;
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
