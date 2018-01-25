#include "card.hpp"
#include "card_information.hpp"

#include <sstream>
#include <stdexcept>

using namespace std;

Card::Card(string name, int8_t tastyness, int8_t price, int8_t size, uint8_t ingame_amount, uint8_t id) :
        name(name), tastyness(tastyness), price(price), size(size), ingame_amount(ingame_amount),
        draw_pile_amount(ingame_amount), id(id) {}

Card::Card(string name, int8_t tastyness, int8_t price, int8_t size, uint8_t ingame_amount, uint8_t draw_pile_amount, uint8_t id) :
        name(name), tastyness(tastyness), price(price), size(size), ingame_amount(ingame_amount),
        draw_pile_amount(draw_pile_amount), id(id) {}

Card::~Card() {}

string Card::str() const {
    stringstream ss;

    ss << name << "[" << (int) id << "]" << "("
    	<< (int) tastyness << ", "
    	<< (int) price << ", "
    	<< (int) size << ", "
    	<< (int) ingame_amount << ")";

    return ss.str();
}

bool Card::is_normal_mushroom() const {
	return id < 9;
}

bool Card::is_mushroom() const {
    return id < 17;
}

bool Card::is_valid_hand_card() const {
    return id < 20;
}

bool Card::is_night_card() const {
    return id >= 9 && id < 17;
}

bool Card::operator<(const Card& other) const {
	return id < other.id;
}

bool Card::operator==(const Card& other) const {
    return id == other.id;
}

const Card& Card::get_night_card() const {
	if (!has_night_card()) {
		throw runtime_error("Does not have a night card");
	}

	return CardInformation::get_card(id + 9);
}

const Card& Card::get_normal_mushroom() const {
    if (!is_night_card()) {
        throw runtime_error("Is not a night card");
    }

    return CardInformation::get_card(id - 9);
}

bool Card::has_night_card() const {
    return is_normal_mushroom() && id != CardInformation::morels().id;
}