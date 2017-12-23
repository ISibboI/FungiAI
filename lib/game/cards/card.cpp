#include "card.hpp"
#include "card_information.hpp"

#include <sstream>

using namespace std;

Card::Card(string name, int8_t tastyness, int8_t price, int8_t size, uint8_t ingame_amount, uint8_t id)
    : name(name), tastyness(tastyness), price(price), size(size), ingame_amount(ingame_amount), id(id) {}

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

bool Card::is_normal_mushroom() {
	return id < 9;
}

bool Card::operator<(const Card& other) {
	return id < other.id;
}

const Card& Card::get_night_card() {
	if (!is_normal_mushroom() || id == CardInformation::morels().id) {
		throw runtime_error("Does not have a night card");
	}

	return CardInformation::get_all_cards()[id + 9];
}