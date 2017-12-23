#ifndef ACTION_HPP
#define ACTION_HPP

#include "game/player.hpp"
#include "game/forest.hpp"

#include <string>

using namespace std;

class Action {
private:
	string name;
	unsigned id;

public:
	Action(const string& name, unsigned id);
	~Action();

	virtual bool execute(Player& player, Forest& forest) const = 0;

	const string& get_name() const;
	unsigned get_id() const;

	virtual string str() const;
	virtual string str(const string& prefix) const = 0;
};

#endif