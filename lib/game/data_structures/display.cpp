#include "display.hpp"
#include "game/cards/card_information.hpp"

using namespace std;

Display::Display(const string& name) : StructuredPile(name) {}

unsigned Display::count_points() const {
	unsigned points = 0;

	for (uint8_t id = 0; id < 19; id++) {
		const Card& card = CardInformation::get_card(id);
		points += card.tastyness * card_count(card);
	}

	return points;
}

unsigned Display::effective_mushroom_count() const {
	unsigned effective_count = 0;

	for (uint8_t id = 0; id < 9; id++) {
		effective_count += card_count(id);
	}

	for (uint8_t id = 9; id < 17; id++) {
		effective_count += 2 * card_count(id);
	}

	return effective_count;
}