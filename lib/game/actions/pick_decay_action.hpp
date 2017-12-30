#ifndef PICK_DECAY_ACTION_HPP
#define PICK_DECAY_ACTION_HPP

#include "action.hpp"
#include "discard_action.hpp"
#include "spdlog.h"

#include <vector>

using namespace std;

class PickDecayAction : public Action {
private:
	DiscardAction* discard_action;
	shared_ptr<spdlog::logger> logger;

public:
	PickDecayAction(DiscardAction* discard_action);
	~PickDecayAction();

	virtual bool execute(Player& player, Forest& forest) override;

	virtual string str(const string& prefix) const override;
};

#endif