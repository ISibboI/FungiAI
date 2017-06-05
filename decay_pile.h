#ifndef DECAY_PILE_H
#define DECAY_PILE_H

#include "cards.h"

#include <cstdint>

class DecayPile {
public:
    DecayPile();
    ~DecayPile();
    
    void add_card(uint8_t id);
    void empty();
    bool is_full();
    void get_cards(uint8_t*& offset, uint8_t*& limit);
    uint8_t size();
    uint8_t net_size();

private:
    static const uint8_t SIZE = 4;
    
    uint8_t pile[SIZE];
    uint8_t limit;
};

#endif // DECAY_PILE_H
