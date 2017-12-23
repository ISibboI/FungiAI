#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "data_structures/hand.hpp"
#include "data_structures/display.hpp"

#include <string>

using namespace std;

class Player {
private:
	Display display;
	Hand hand;
	string name;

public:
	Player(const string& name);
};

#endif