#ifndef PILE_H
#define PILE_H

#include <cstdint>
#include <string>

class Pile {
public:
    Pile(std::string name, uint8_t max_limit);
    ~Pile();

    void add_card(uint8_t id);
    uint8_t remove_card(uint8_t index);
    void clear();
    bool is_full();
    void get_cards(uint8_t*& offset, uint8_t*& limit);
    uint8_t* get_offset();
    uint8_t* get_limit();
    uint8_t size();
    int8_t pick_all_size();
    virtual std::string str();
    uint8_t operator[](uint8_t index);

protected:
    std::string name;
    uint8_t* pile;
    uint8_t max_limit;
    uint8_t limit;
};

#endif // PILE_H
