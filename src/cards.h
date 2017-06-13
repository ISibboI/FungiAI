#ifndef CARDS_H
#define CARDS_H

#include <string>

class Card {
public:
    const std::string name;
    const int8_t tastyness;
    const int8_t price;
    const int8_t size;

    Card(std::string name, int8_t tastyness, int8_t price, int8_t size);
    ~Card();
    std::string str() const;
};

const uint8_t cards_size = 24;

const Card cards[cards_size]= {
   Card("Honey fungus", 1, 1, 1),
   Card("Tree Ear", 1, 2, 1),
   Card("Lawyer's Wig", 2, 1, 1),
   Card("Shiitake", 2, 2, 1),
   Card("Hen of the Woods", 3, 1, 1),
   Card("Birch bolete", 3, 2, 1),
   Card("Porcini", 3, 3, 1),
   Card("Chanterelle", 4, 2, 1),
   Card("Morels", 6, 4, 1),
   Card("Night Honey fungus", 2, 2, 1),
   Card("Night Tree Ear", 2, 4, 1),
   Card("Night Lawyer's Wig", 4, 2, 1),
   Card("Night Shiitake", 4, 4, 1),
   Card("Night Hen of the Woods", 6, 2, 1),
   Card("Night Birch bolete", 6, 4, 1),
   Card("Night Porcini", 6, 6, 1),
   Card("Night Chanterelle", 8, 4, 1),
   Card("Butter", 3, 4, 1),
   Card("Cidre", 5, 5, 1),
   Card("Pan", -1, -1, 1),
   Card("Basket", -1, -1, -2),
   Card("Moon", -1, -1, 0),
   Card("Fly agaric", -1, -1, 0),
   Card("Stick", -1, -1, 0)
};

const uint8_t cards_max[cards_size] {
    10, 8, 6, 5, 5, 4, 4, 4, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 11, 10, 8, 5, 30
};

const uint8_t cards_max_sum = 10 + 8 + 6 + 5 + 5 + 4 + 4 + 4 + 3 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 3 + 3 + 11 + 10 + 8 + 5 + 30;

const uint8_t lower_pair_shroom_max_id = 7;
const uint8_t night_min_id = 9;
const uint8_t night_max_id = 16;
const uint8_t special_min_id = 20;
const uint8_t shroom_max_id = 18;
const uint8_t to_night_card = 9;

const uint8_t butter = 17;
const uint8_t cidre = 18;
const uint8_t pan = 19;
const uint8_t basket = 20;
const uint8_t moon = 21;
const uint8_t fly_agaric = 22;
const uint8_t stick = 23;

#endif // CARDS_H
