#ifndef DISCARD_ACTION_HPP
#define DISCARD_ACTION_HPP

#include "action.hpp"
#include "spdlog.h"

#include <vector>

using namespace std;

class DiscardAction : public Action {
private:
	vector<uint8_t> discard_order;
	shared_ptr<spdlog::logger> logger;

	DiscardAction();

public:
	DiscardAction(vector<uint8_t>&& discard_order);
	DiscardAction(DiscardAction&& discard_action);
	~DiscardAction();

	virtual bool execute(Player& player, Forest& forest) override;

	virtual string str(const string& prefix) const override;
};

#endif