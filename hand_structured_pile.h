#ifndef HAND_STRUCTURED_PILE_H
#define HAND_STRUCTURED_PILE_H

#include "structured_pile.h"

class HandStructuredPile : public StructuredPile {
public:
    HandStructuredPile(std::string name);
    ~HandStructuredPile();

    void add_card(uint8_t id);
    void add_cards(uint8_t id, uint8_t count);
    void remove_card(uint8_t id);
    void remove_cards(uint8_t id, uint8_t count);

    uint8_t get_night_card_count();

    std::string str();

    int8_t get_remaining_capacity(StructuredPile& display);
    uint8_t get_effective_shroom_count(uint8_t id);

private:
    uint8_t night_card_sum;
};

#endif // HAND_STRUCTURED_PILE_H
