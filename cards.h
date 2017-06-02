#ifndef CARDS_H
#define CARDS_H

#include <string>

class Card {
public:
    const std::string name;
    const uint8_t tastyness;
    const uint8_t price;

    Card(std::string name, int8_t tastyness, int8_t price);
    ~Card();
    std::string str() const;
};

const uint8_t cards_size = 24;

const Card cards[cards_size]= {
   Card("Honey fungus", 1, 1),
   Card("Tree Ear", 1, 2),
   Card("Lawyer's Wig", 2, 1),
   Card("Shiitake", 2, 2),
   Card("Hen of the Woods", 3, 1),
   Card("Birch bolete", 3, 2),
   Card("Porcini", 3, 3),
   Card("Chanterelle", 4, 2),
   Card("Morels", 6, 4),
   Card("Night Honey fungus", 2, 2),
   Card("Night Tree Ear", 2, 4),
   Card("Night Lawyer's Wig", 4, 2),
   Card("Night Shiitake", 4, 4),
   Card("Night Hen of the Woods", 6, 2),
   Card("Night Birch bolete", 6, 4),
   Card("Night Porcini", 6, 6),
   Card("Night Chanterelle", 8, 4),
   Card("Butter", 3, 4),
   Card("Cidre", 5, 5),
   Card("Pan", -1, -1),
   Card("Basket", -1, -1),
   Card("Moon", -1, -1),
   Card("Fly agaric", -1, -1),
   Card("Stick", -1, -1)
};

const uint8_t night_min_id = 9;
const uint8_t night_max_id = 16;
const uint8_t special_min_id = 20;

const uint8_t butter = 17;
const uint8_t cidre = 18;
const uint8_t pan = 19;
const uint8_t basket = 20;
const uint8_t moon = 21;
const uint8_t fly_agaric = 22;
const uint8_t stick = 23;

#endif // CARDS_H
