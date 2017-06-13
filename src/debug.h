#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <iostream>

#ifdef DEBUG

#define print_var(a) cout << #a << ": " << (unsigned) a << endl;
#define print_svar(a) cout << #a << ": " << (int) a << endl;
#define print_sizeof(a) cout << #a << sizeof(a) << endl;
#define print(a) cout << (a) << endl;

#else

#define print_var(a)
#define print_svar(a)
#define print_sizeof(a)
#define print(a)

#endif // DEBUG

void print_array(const std::string& name, uint8_t* array, size_t size);

#endif // DEBUG_H
