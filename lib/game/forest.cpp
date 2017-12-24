#include "forest.hpp"
#include "cards/card_information.hpp"
#include "io/strings.hpp"

#include <random>
#include <algorithm>
#include <sstream>

using namespace std;

Forest::Forest() : discard_pile("Discard Pile"), logger(spdlog::get("Forest")) {}

void Forest::initialize(mt19937_64& random_engine) {
	draw_pile = CardInformation::create_initial_draw_pile();
	shuffle(draw_pile.begin(), draw_pile.end(), random_engine);

	forest.clear();
	decay_pile.clear();
	discard_pile.clear();

	fill_forest();
	logger->trace("Initialized forest");
}

vector<uint8_t>& Forest::get_draw_pile() {
	return draw_pile;
}

vector<uint8_t>& Forest::get_forest() {
	return forest;
}

const vector<uint8_t>& Forest::get_forest() const {
	return forest;
}

vector<uint8_t>& Forest::get_decay_pile() {
	return decay_pile;
}

StructuredPile& Forest::get_discard_pile() {
	return discard_pile;
}

void Forest::post_turn_actions() {
	if (decay_pile.size() == 4) {
		for (uint8_t id : decay_pile) {
			discard_pile.add_card(id);
		}

		decay_pile.clear();
		logger->trace("Cleared decay pile");
	}

	decay_pile.push_back(forest.front());
	forest.erase(forest.begin());
	fill_forest();
}

void Forest::fill_forest() {
	unsigned count = 0;

	while (forest.size() < 8 && draw_pile.size() > 0) {
		forest.push_back(draw_pile.back());
		draw_pile.pop_back();
		count++;
	}

	logger->trace("Filled forest with {:d} cards", count);
}

string Forest::str() const {
	return str("");
}

string Forest::str(const string& prefix) const {
	stringstream ss;
	ss << prefix << "Forest:\n";
	ss << prefix << "  Draw pile: " << Strings::str(draw_pile) << "\n";
	ss << prefix << "  Forest: " << Strings::str(forest) << "\n";
	ss << prefix << "  Decay pile: " << Strings::str(decay_pile) << "\n";
	ss << discard_pile.str(prefix + "  ");
	return ss.str();
}