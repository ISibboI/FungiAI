#ifndef FOREST_HPP
#define FOREST_HPP

#include "cards/card.hpp"
#include "data_structures/structured_pile.hpp"

#include <vector>
#include <random>

using namespace std;

class Forest {
private:
	vector<uint8_t> draw_pile;
	vector<uint8_t> forest;
	vector<uint8_t> decay_pile;
	StructuredPile discard_pile;

public:
	Forest();

	void initialize(mt19937_64& random_engine);

	vector<uint8_t>& get_draw_pile();
	vector<uint8_t>& get_forest();
	vector<uint8_t>& get_decay_pile();
	StructuredPile& get_discard_pile();

	string str() const;
	string str(const string& prefix) const;
};

#endif