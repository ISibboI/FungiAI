#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "data_structures/hand.hpp"
#include "data_structures/display.hpp"
#include "forest.hpp"

#include <string>

using namespace std;

class Player {
private:
	string name;
	Display display;
	Hand hand;
	uint8_t fly_agaric_timer;

public:
	Player(const string& name);

	void initialize(Forest& forest);

	void draw_initial_card(Forest& forest);

	unsigned get_hand_capacity();

	Hand& get_hand();
	Display& get_display();

	void set_fly_agaric_timer();
	void update();

	string str() const;
	string str(const string& prefix) const;
};

#endif