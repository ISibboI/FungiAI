#ifndef HAND_STRUCTURED_PILE_H
#define HAND_STRUCTURED_PILE_H

#include "structured_pile.h"

class HandStructuredPile : public StructuredPile {
public:
    HandStructuredPile(std::string name);
    ~HandStructuredPile();
    
    void add_card(uint8_t id);
    void remove_card(uint8_t id);
    
    uint8_t get_night_card_count();
    
    std::string str();
    
private:
    uint8_t night_card_sum;
};

#endif // HAND_STRUCTURED_PILE_H