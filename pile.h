#ifndef PILE_H
#define PILE_H

#include "structured_pile.h"

#include <cstdint>
#include <string>

class Pile {
public:
    Pile(std::string name, uint8_t max_limit);
    ~Pile();

    void add_card(uint8_t id);
    void add_cards(const uint8_t* ids, uint8_t length);
    uint8_t remove_card(uint8_t index);
    uint8_t remove_last_card();
    void remove_cards(uint8_t index, uint8_t length, uint8_t* destination);
    void make_space(uint8_t length);
    void clear();

    void get_cards(uint8_t*& offset, uint8_t*& limit);
    uint8_t* get_offset();
    uint8_t* get_limit();
    uint8_t operator[](uint8_t index);

    uint8_t size();
    bool is_full();
    int8_t pick_all_size();

    StructuredPile* structurize();

    std::string str();

    void encode_for_nn(float* params);
    size_t get_nn_encoding_size();

protected:
    std::string name;
    uint8_t* pile;
    uint8_t max_limit;
    uint8_t limit;
};

#endif // PILE_H
