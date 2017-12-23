#ifndef PILE_HPP
#define PILE_HPP

#include <string>

using namespace std;

class Pile {
private:
    const string name;

public:
    Pile(const string& name);
    virtual ~Pile();

    const string& get_name();

    virtual unsigned size() = 0;
};

#endif
