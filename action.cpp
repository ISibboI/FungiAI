#include "action.h"

Action::Action(uint8_t id, uint8_t target, uint8_t count, StructuredPile* drop_ids,
    StructuredPile* display, StructuredPile* hand) : id(id), target(target),
    count(count), drop_ids(drop_ids), display(display), hand(hand) {}

// TODO
Action(uint8_t id, uint8_t target, StructuredPile* drop_ids,
    StructuredPile* display, StructuredPile* hand);

// TODO
Action(uint8_t id, uint8_t target, uint8_t count,
    StructuredPile* display, StructuredPile* hand);

// TODO
Action(uint8_t id, StructuredPile* display, StructuredPile* hand);

Action::~Action() {}
