#include "hand.hpp"

#include <sstream>
#include <stdexcept>

using namespace std;

Hand::Hand(const string& name) : StructuredPile(name) {}

Hand::~Hand() {}

void Hand::add_cards(const Card& card, unsigned count) {
    ensure_valid_hand_card(card);
    StructuredPile::add_cards(card, count);
}

void Hand::remove_cards(const Card& card, unsigned count) {
    ensure_valid_hand_card(card);
    StructuredPile::remove_cards(card, count);
}

unsigned Hand::card_count(const Card& card) {
    ensure_valid_hand_card(card);
    return StructuredPile::card_count(card);
}

void Hand::ensure_valid_hand_card(const Card& card) {
    if (!card.is_valid_hand_card()) {
        throw runtime_error("Not a valid hand card");
    }
}
