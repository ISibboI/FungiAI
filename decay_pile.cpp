#include "decay_pile.h"

#include <sstream>
#include <iostream>

using namespace std;

DecayPile::DecayPile() : Pile(4) {}

DecayPile::~DecayPile() {}

int8_t DecayPile::net_size() {
    int8_t result = 0;
    
    for (unsigned i = 0; i < limit; i++) {
        if (pile[i] == basket) {
            result -= 2;
        } else if (pile[i] < special_min_id) {
            result++;
        }
    }
    
    return result;
}

string DecayPile::str() {
    stringstream ss;
    
    ss << "Decay pile: " << Pile::str();
    
    return ss.str();
}
