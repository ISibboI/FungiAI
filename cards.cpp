#include "cards.h"

#include <sstream>

using namespace std;

Card::Card(string name, int8_t tastyness, int8_t price)
    : name(name), tastyness(tastyness), price(price) {}

Card::~Card() {}

string Card::str() const {
    stringstream ss;

    ss << name << "(" << (unsigned) tastyness << ", " << (unsigned) price << ")";

    return ss.str();
}
