#include "pile.hpp"

using namespace std;

Pile::Pile(const string& name) : name(name) {}

Pile::~Pile() {}

const string& Pile::get_name() {
    return name;
}