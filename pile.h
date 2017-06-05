#ifndef PILE_H
#define PILE_H

#include <cstdint>
#include <string>

class Pile {
public:
    void add_card(uint8_t id);
    void clear();
    bool is_full();
    void get_cards(uint8_t*& offset, uint8_t*& limit);
    uint8_t* get_offset();
    uint8_t* get_limit();
    uint8_t size();
    virtual std::string str();

protected:
    Pile(uint8_t max_limit);
    ~Pile();
    
    uint8_t* pile;
    uint8_t max_limit;
    uint8_t limit;
};

#endif // PILE_H
