#include "cards.h"

#include <sstream>

using namespace std;

Card::Card(string name, int8_t tastyness, int8_t price)
    : name(name), tastyness(tastyness), price(price) {}

Card::~Card() {}

string Card::str() const {
    stringstream ss;

    ss << name << "(" << tastyness << ", " << price << ")";

    return ss.str();
}
