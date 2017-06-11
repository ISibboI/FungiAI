#ifndef ACTION_H
#define ACTION_H

#include "structured_pile.h"
#include "hand_structured_pile.h"

#include <string>

class Action {
public:
    Action(uint8_t id, uint8_t target, uint8_t count, StructuredPile* drop_ids,
        StructuredPile* display, HandStructuredPile* hand);
    Action(uint8_t id, uint8_t target, StructuredPile* drop_ids,
        StructuredPile* display, HandStructuredPile* hand);
    Action(uint8_t id, StructuredPile* drop_ids,
        StructuredPile* display, HandStructuredPile* hand);
    Action(uint8_t id, uint8_t target, uint8_t count,
        StructuredPile* display, HandStructuredPile* hand);
    Action(uint8_t id, StructuredPile* display, HandStructuredPile* hand);
    Action();
    ~Action();

    uint8_t id;
    uint8_t target;
    uint8_t count;
    StructuredPile* drop_ids;
    StructuredPile* display;
    HandStructuredPile* hand;

    std::string str();

    Action(float* params, StructuredPile* display, HandStructuredPile* hand);
    static size_t get_nn_decoding_size();
};

#endif // ACTION_H
