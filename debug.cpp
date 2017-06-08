#include "debug.h"

#include <iostream>
#include <string>

using namespace std;

#ifdef DEBUG

void print_array(const string& name, uint8_t* array, size_t size) {
    cout << name << " = [";

    if (size > 0) {
        for (size_t i = 0; i < size - 1; i++) {
            cout << (unsigned) array[i] << ", ";
        }

        cout << (unsigned) array[size - 1];
    }

    cout << "]\n" << flush;
}

#else

void print_array(const string& name, uint8_t* array, size_t size) {}

#endif // DEBUG
