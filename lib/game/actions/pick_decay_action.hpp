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
	explicit PickDecayAction(DiscardAction* discard_action);
	~PickDecayAction() override = default;

	bool execute(Player& player, Forest& forest) override;

	string str(const string& prefix) const override;
};

#endif