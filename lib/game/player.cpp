#include "player.hpp"
#include "cards/card_information.hpp"

#include <sstream>

using namespace std;

Player::Player(const string& name) :
	name(name),
	hand(name + "'s hand"),
	display(name + "'s display") {}

void Player::initialize(Forest& forest) {
	display.clear();
	hand.clear();

	display.add_card(CardInformation::pan());

	for (unsigned i = 0; i < 3; i++) {
		draw_initial_card(forest);
	}
}

void Player::draw_initial_card(Forest& forest) {
	uint8_t id = forest.get_draw_pile().back();
	forest.get_draw_pile().pop_back();
	const Card& card = CardInformation::get_card(id);

	if (card.is_valid_hand_card()) {
		hand.add_card(card);
	} else if (card == CardInformation::basket()) {
		display.add_card(card);
	} else if (card == CardInformation::fly_agaric()) {
		// Just for initialization, so no need to discard anything
		forest.get_discard_pile().add_card(card);
	}
}

string Player::str() const {
	return str("");
}
	
string Player::str(const string& prefix) const {
	stringstream ss;
	ss << prefix << "Player " << name << ":\n";
	ss << hand.str(prefix + "  ") << "\n";
	ss << display.str(prefix + "  ");
	return ss.str();
}