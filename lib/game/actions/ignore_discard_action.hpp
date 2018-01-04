#ifndef IGNORE_DISCARD_ACTION_HPP
#define IGNORE_DISCARD_ACTION_HPP

#include "discard_action.hpp"

class IgnoreDiscardAction : public DiscardAction {
private:
	unsigned discard_count;

public:
	IgnoreDiscardAction();
	virtual ~IgnoreDiscardAction();

	virtual bool execute(Player& player, Forest& forest) override;

	virtual string str(const string& prefix) const override;

	unsigned get_discard_count();
};

#endif