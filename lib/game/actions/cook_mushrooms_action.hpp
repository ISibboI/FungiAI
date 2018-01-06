#ifndef COOK_MUSHROOMS_ACTION_HPP
#define COOK_MUSHROOMS_ACTION_HPP

#include "action.hpp"
#include "spdlog.h"

#include <vector>

using namespace std;

class CookMushroomsAction : public Action {
private:
	vector<uint8_t> cook_order;
	shared_ptr<spdlog::logger> logger;

public:
    CookMushroomsAction();
	explicit CookMushroomsAction(vector<uint8_t> cook_order);
	~CookMushroomsAction() override = default;

	virtual bool execute(Player& player, Forest& forest) override;
	void add_optimal_amount_of_ingredients(Player& player, unsigned effective_card_count) const;

	virtual string str(const string& prefix) const override;

	vector<uint8_t>& get_cook_order();
};

#endif