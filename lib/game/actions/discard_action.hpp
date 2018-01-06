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

protected:
	DiscardAction(const string& name, unsigned id);

public:
	DiscardAction();
	explicit DiscardAction(vector<uint8_t> discard_order);
	DiscardAction(DiscardAction&& discard_action) noexcept;
	virtual ~DiscardAction() = default;

	bool execute(Player& player, Forest& forest) override;

	string str(const string& prefix) const override;

	vector<uint8_t>& get_discard_order();
};

#endif