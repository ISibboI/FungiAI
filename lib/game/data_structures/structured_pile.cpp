#include "structured_pile.hpp"
#include "game/cards/card_information.hpp"

#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <sstream>

using namespace std;

StructuredPile::StructuredPile(const string& name) :
    Pile(name),
    all_cards_count(0),
    cards(CardInformation::get_all_cards().size(), 0) {}

unsigned StructuredPile::size() const {
    return all_cards_count;
}

void StructuredPile::add_card(const Card& card) {
    add_cards(card, 1);
}

void StructuredPile::add_cards(const Card& card, unsigned count) {
    check_size();

    unsigned new_count = count + cards[card.id];

//#ifndef NDEBUG
    if (new_count < count || new_count > card.ingame_amount) {
        throw runtime_error("Illegal card count");
    }
//#endif

    cards[card.id] = (uint8_t) new_count;
    all_cards_count += count;
}

void StructuredPile::remove_card(const Card& card) {
    remove_cards(card, 1);
}

void StructuredPile::remove_cards(const Card& card, unsigned count) {
    check_size();

    unsigned new_count = cards[card.id] - count;

#ifndef NDEBUG
    if (new_count > cards[card.id]) {
        throw runtime_error("Illegal card count");
    }
#endif

    cards[card.id] = (uint8_t) new_count;
    all_cards_count -= count;
}

unsigned StructuredPile::card_count(const Card& card) const {
    check_size();
    return cards[card.id];
}

void StructuredPile::add_card(uint8_t id) {
    add_card(CardInformation::get_card(id));
}

void StructuredPile::add_cards(uint8_t id, unsigned count) {
    add_cards(CardInformation::get_card(id), count);
}

void StructuredPile::remove_card(uint8_t id) {
    remove_card(CardInformation::get_card(id));
}

void StructuredPile::remove_cards(uint8_t id, unsigned count) {
    remove_cards(CardInformation::get_card(id), count);
}

unsigned StructuredPile::card_count(uint8_t id) const {
    return card_count(CardInformation::get_card(id));
}

void StructuredPile::check_size() const {
    #ifndef NDEBUG
    if (std::accumulate(cards.begin(), cards.end(), 0) != size()) {
        throw runtime_error("Size check failed");
    }
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
