#ifndef PICK_ACTION_HPP
#define PICK_ACTION_HPP

#include "action.hpp"
#include "discard_action.hpp"
#include "spdlog.h"

#include <vector>

using namespace std;

class PickAction : public Action {
private:
	vector<uint8_t> pick_order;
	DiscardAction* discard_action;
	shared_ptr<spdlog::logger> logger;

public:
    explicit PickAction(DiscardAction* discard_action);
	PickAction(vector<uint8_t> pick_order, DiscardAction* discard_action);
	~PickAction() = default;

	bool execute(Player& player, Forest& forest) override;

	string str(const string& prefix) const override;

	vector<uint8_t>& get_pick_order();
};

#endif