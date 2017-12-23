#include "forest.hpp"
#include "cards/card_information.hpp"
#include "io/strings.hpp"

#include <random>
#include <algorithm>
#include <sstream>

using namespace std;

Forest::Forest() : discard_pile("Discard Pile") {}

void Forest::initialize(mt19937_64& random_engine) {
	draw_pile = CardInformation::create_initial_draw_pile();
	shuffle(draw_pile.begin(), draw_pile.end(), random_engine);

	forest.clear();
	decay_pile.clear();
	discard_pile.clear();
}

vector<uint8_t>& Forest::get_draw_pile() {
	return draw_pile;
}

vector<uint8_t>& Forest::get_forest() {
	return forest;
}

vector<uint8_t>& Forest::get_decay_pile() {
	return decay_pile;
}

StructuredPile& Forest::get_discard_pile() {
	return discard_pile;
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
	ss << prefix << "  " << discard_pile.str(prefix + "  ");
	return ss.str();
}