#ifndef STRUCTURED_PILE_H
#define STRUCTURED_PILE_H

#include "cards.h"

#include <string>

class StructuredPile {
public:
    StructuredPile(std::string name);
    ~StructuredPile();
    
    virtual void add_card(uint8_t id);
    virtual void remove_card(uint8_t id);
    
    uint8_t get_count(uint8_t id);
    uint8_t operator[](uint8_t id);
    uint8_t size();
    
    virtual std::string str();
    
private:
    static const uint8_t LIMIT = 255;
    std::string name;
    uint8_t pile[cards_size];
    uint8_t sum;
};

#endif // STRUCTURED_PILE_H
