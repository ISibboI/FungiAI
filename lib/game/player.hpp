#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "data_structures/hand.hpp"
#include "data_structures/display.hpp"
#include "forest.hpp"

#include <string>

using namespace std;

class Player {
private:
	Display display;
	Hand hand;
	string name;

public:
	Player(const string& name);

	void initialize(Forest& forest);

	void draw_initial_card(Forest& forest);

	string str() const;
	string str(const string& prefix) const;
};

#endif