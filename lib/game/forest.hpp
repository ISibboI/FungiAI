#ifndef FOREST_HPP
#define FOREST_HPP

#include "cards/card.hpp"
#include "data_structures/structured_pile.hpp"

#include <vector>

using namespace std;

class Forest {
private:
	vector<uint8_t> draw_pile;
	vector<uint8_t> forest;
	vector<uint8_t> decay_pile;
	StructuredPile discard_pile;

public:
	Forest();

	void initialize();
};

#endif