#ifndef NN_ENCODING_H
#define NN_ENCODING_H

#include <cstdint>
#include <stdexcept>

using namespace std;

inline float* nn_encode_int_unary(float* params, uint8_t n, uint8_t max_n) {
    if (n > max_n) {
        throw runtime_error("n exceeds max");
    }

    unsigned i = 0;

    for (; i < n; i++) {
        *(params++) = 1;
    }

    for (; i < max_n; i++) {
        *(params++) = 0;
    }

    return params;
}

#endif // NN_ENCODING_H
