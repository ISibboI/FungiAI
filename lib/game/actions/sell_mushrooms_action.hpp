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
	SellMushroomsAction();
	explicit SellMushroomsAction(vector<uint8_t> sell_order);
	~SellMushroomsAction() override = default;

	bool execute(Player& player, Forest& forest) override;

	string str(const string& prefix) const override;

	vector<uint8_t>& get_sell_order();
};

#endif