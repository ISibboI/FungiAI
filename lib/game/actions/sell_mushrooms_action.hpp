#ifndef SELL_MUSHROOMS_ACTION_HPP
#define SELL_MUSHROOMS_ACTION_HPP

#include "action.hpp"
#include "spdlog.h"

#include <vector>

using namespace std;

class SellMushroomsAction : public Action {
private:
	vector<uint8_t> sell_order;
	shared_ptr<spdlog::logger> logger;

public:
	SellMushroomsAction(vector<uint8_t>&& sell_order);
	~SellMushroomsAction();

	virtual bool execute(Player& player, Forest& forest) const override;

	virtual string str(const string& prefix) const override;
};

#endif