#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action {
public:
    Action(uint8_t id, uint8_t target, uint8_t count, StructuredPile* drop_ids,
        StructuredPile* display, StructuredPile* hand);
    Action(uint8_t id, uint8_t target, StructuredPile* drop_ids,
        StructuredPile* display, StructuredPile* hand);
    Action(uint8_t id, uint8_t target, uint8_t count,
        StructuredPile* display, StructuredPile* hand);
    Action(uint8_t id, StructuredPile* display, StructuredPile* hand);
    ~Action();

    uint8_t id;
    uint8_t target;
    uint8_t count;
    StructuredPile* drop_ids;
    StructuredPile* display;
    StructuredPile* hand;

    std::string str();
};

#endif // ACTION_H
