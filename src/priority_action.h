#ifndef PRIORITY_ACTION_H
#define PRIORITY_ACTION_H

#include "structured_pile.h"
#include "hand_structured_pile.h"

#include <string>

class PriorityAction {
private:
	vector<uint8_t> ids;
	vector<uint8_t> targets;
	vector<uint8_t> counts;
	vector<vector<uint8_t>> drop_ids;

	StructuredPile* display;
	HandStructuredPile* hand;

public:
	PriorityAction(float* params, StructuredPile* display, HandStructuredPile* hand);
}

#endif // PRIORITY_ACTION_H