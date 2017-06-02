#ifndef DEBUG_H
#define DEBUG_H

#include <string>

#ifdef DEBUG

#define print_sizeof(a) cout << "a" << sizeof(a) << endl;

#else

#define print_sizeof(a)

#endif // DEBUG

void print_array(const std::string& name, uint8_t* array, size_t size);

#endif // DEBUG_H
