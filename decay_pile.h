#ifndef DECAY_PILE_H
#define DECAY_PILE_H

#include "cards.h"
#include "pile.h"

#include <cstdint>
#include <string>

class DecayPile : public Pile {
public:
    DecayPile();
    ~DecayPile();
    
    int8_t net_size();
    std::string str();
};

#endif // DECAY_PILE_H
