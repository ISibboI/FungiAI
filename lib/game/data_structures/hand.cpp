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

unsigned Hand::effective_card_count(const Card& card) const {
    unsigned night_card_count = 0;

    if (card.has_night_card()) {
        const Card& night_card = card.get_night_card();
        night_card_count += card_count(night_card) * 2;
    }

    return card_count(card) + night_card_count;
}

unsigned Hand::effective_card_count(uint8_t id) const {
    return effective_card_count(CardInformation::get_card(id));
}

void Hand::ensure_valid_hand_card(const Card& card) const {
    if (!card.is_valid_hand_card()) {
        throw runtime_error("Not a valid hand card");
    }
}
