#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>

using namespace std;

class Card {
public:
    const string name;
    const int8_t tastyness;
    const int8_t price;
    const int8_t size;
    const uint8_t ingame_amount;
    const uint8_t id;

    Card(string name, int8_t tastyness, int8_t price, int8_t size, uint8_t ingame_amount, uint8_t id);
    ~Card();
    string str() const;

    bool is_normal_mushroom() const;
    bool is_valid_hand_card() const;
    bool is_night_card() const;

    bool operator<(const Card& other) const;
    bool operator==(const Card& other) const;

    const Card& get_night_card() const;
    bool has_night_card() const;
};

#endif
