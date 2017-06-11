#ifndef NN_ENCODING_H
#define NN_ENCODING_H

#include "structured_pile.h"

#include <cstdint>
#include <stdexcept>

using namespace std;

inline void nn_encode_int_unary(float** params, uint8_t n, uint8_t max_n) {
    if (n > max_n) {
        throw runtime_error("n exceeds max");
    }

    unsigned i = 0;

    for (; i < n; i++) {
        *((*params)++) = 1;
    }

    for (; i < max_n; i++) {
        *((*params)++) = 0;
    }
}

inline uint8_t nn_decode_int_one_of_n(float** params, uint8_t max_n) {
    uint8_t max_index = 0;
    float max = *((*params)++);

    for (uint8_t i = 1; i < max_n; i++) {
        if (**params > max) {
            max = **params;
            max_index = i;
        }

        (*params)++;
    }

    return max_index;
}

inline StructuredPile* nn_decode_drop_ids(float** params) {
    StructuredPile* drop_ids = new StructuredPile("Drop ids");
    float* p_current = *params;

    for (unsigned i = 0; i < 4; i++) {
        uint8_t max_index = 0;
        float max = *(p_current++);

        for (unsigned mi = 1; mi < special_min_id + 1; i++) {
            if (*p_current > max) {
                max = *p_current;
                max_index = mi;
            }
        }

        if (max_index != special_min_id) {
            drop_ids->add_card(max_index);
        }
    }

    return drop_ids;
}

#endif // NN_ENCODING_H
