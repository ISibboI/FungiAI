#include "hand.hpp"
#include "game/cards/card_information.hpp"

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

unsigned Hand::card_count(const Card& card) const {
    ensure_valid_hand_card(card);
    return StructuredPile::card_count(card);
}

void Hand::add_cards(uint8_t id, unsigned count) {
    add_cards(CardInformation::get_card(id), count);
}

void Hand::remove_cards(uint8_t id, unsigned count) {
    remove_cards(CardInformation::get_card(id), count);
}

unsigned Hand::card_count(uint8_t id) const {
    return card_count(CardInformation::get_card(id));
}

void Hand::ensure_valid_hand_card(const Card& card) const {
    if (!card.is_valid_hand_card()) {
        throw runtime_error("Not a valid hand card");
    }
}
