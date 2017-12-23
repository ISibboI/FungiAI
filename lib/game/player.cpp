#include "player.hpp"

using namespace std;

Player::Player(const string& name) :
	name(name),
	hand(name + "'s hand"),
	display(name + "'s display") {}