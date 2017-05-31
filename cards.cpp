#include "cards.h"

using namespace std;

Card::Card(string name, int8_t tastyness, int8_t price)
    : name(name), tastyness(tastyness), price(price) {}

Card::~Card() {}
