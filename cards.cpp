#include "cards.h"

#include <sstream>

using namespace std;

Card::Card(string name, int8_t tastyness, int8_t price, int8_t size)
    : name(name), tastyness(tastyness), price(price), size(size) {}

Card::~Card() {}

string Card::str() const {
    stringstream ss;

    ss << name << "(" << (int) tastyness << ", " << (int) price << ", " << (int) size << ")";

    return ss.str();
}
