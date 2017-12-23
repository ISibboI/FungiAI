#include "structured_pile.hpp"
#include "game/cards/card_information.hpp"

#include <stdexcept>
#include <algorithm>
#include <sstream>

using namespace std;

StructuredPile::StructuredPile(const string& name) :
    Pile(name),
    all_cards_count(0),
    cards(CardInformation::get_all_cards().size(), 0) {}

StructuredPile::~StructuredPile() {}

unsigned StructuredPile::size() const {
    return all_cards_count;
}

void StructuredPile::add_card(const Card& card) {
    add_cards(card, 1);
}

void StructuredPile::add_cards(const Card& card, unsigned count) {
    check_size();

    unsigned new_count = count + cards[card.id];

    if (new_count < count || new_count > card.ingame_amount) {
        throw runtime_error("Illegal card count");
    }

    cards[card.id] = new_count;
}

void StructuredPile::remove_card(const Card& card) {
    remove_cards(card, 1);
}

void StructuredPile::remove_cards(const Card& card, unsigned count) {
    check_size();

    unsigned new_count = cards[card.id] - count;

    if (new_count > cards[card.id]) {
        throw runtime_error("Illegal card count");
    }

    cards[card.id] = new_count;
}

unsigned StructuredPile::card_count(const Card& card) {
    check_size();
    return cards[card.id];
}

void StructuredPile::check_size() {
    #ifdef DEBUG
    #ifndef NDEBUG
    if (accumulate(cards.begin(), cards.end(), 0) != size) {
        throw runtime_error("Size check failed");
    }
    #endif
    #endif
}

const vector<uint8_t>& StructuredPile::get_card_counts() {
    return cards;
}

void StructuredPile::clear() {
    all_cards_count = 0;
    cards.clear();
    cards.insert(cards.begin(), CardInformation::get_all_cards().size(), 0);
}

string StructuredPile::str() const {
    return str("");
}

string StructuredPile::str(const string& prefix) const {
    stringstream ss;
    ss << prefix << get_name() << ":";

    for (const Card& card : CardInformation::get_all_cards()) {
        if (cards[card.id] > 0) {
            ss << "\n" << prefix << "  " << card.name << ": " << (int) cards[card.id];
        }
    }

    return ss.str();
}
