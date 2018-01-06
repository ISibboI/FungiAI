#ifndef PLACE_PAN_ACTION_HPP
#define PLACE_PAN_ACTION_HPP

#include "action.hpp"
#include "spdlog.h"

using namespace std;

class PlacePanAction : public Action {
private:
	shared_ptr<spdlog::logger> logger;

public:
	PlacePanAction();
	~PlacePanAction() override = default;

	bool execute(Player& player, Forest& forest) override;

	string str(const string& prefix) const override;
};

#endif