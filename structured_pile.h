#ifndef STRUCTURED_PILE_H
#define STRUCTURED_PILE_H

#include "cards.h"

#include <string>

class StructuredPile {
public:
    StructuredPile(std::string name);
    virtual ~StructuredPile();

    virtual void add_card(uint8_t id);
    virtual void add_cards(uint8_t id, uint8_t count);
    virtual void remove_card(uint8_t id);
    virtual void remove_cards(uint8_t id, uint8_t count);
    void set_cards(uint8_t id, uint8_t new_count);

    bool remove_shrooms_maximizing_space(uint8_t id, uint8_t count);

    uint8_t get_count(uint8_t id);
    uint8_t operator[](uint8_t id);
    uint8_t size();
    int8_t pick_all_size();

    virtual std::string str();

private:
    static const uint8_t LIMIT = 255;
    std::string name;
    uint8_t pile[cards_size];
    uint8_t sum;
    int8_t size_sum;
};

#endif // STRUCTURED_PILE_H
