#ifndef PICK_ACTION_HPP
#define PICK_ACTION_HPP

#include "action.hpp"
#include "discard_action.hpp"
#include "spdlog.h"

#include <vector>

using namespace std;

class PickAction : Action {
private:
	vector<uint8_t> pick_order;
	DiscardAction discard_action;
	shared_ptr<spdlog::logger> logger;

public:
	PickAction(vector<uint8_t>&& pick_order, DiscardAction&& discard_action);
	~PickAction();

	virtual bool execute(Player& player, Forest& forest) const override;

	virtual string str(const string& prefix) const override;
};

#endif