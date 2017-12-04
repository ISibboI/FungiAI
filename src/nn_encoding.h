#ifndef NN_ENCODING_H
#define NN_ENCODING_H

#include "structured_pile.h"
#include "debug.h"

#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

inline void nn_encode_int_unary(float** params, uint8_t n, uint8_t max_n) {
    if (n > max_n) {
        print_var(n);
        print_var(max_n);
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

inline vector<uint8_t> nn_decode_int_one_of_n_list(float** params, uint8_t max_n) {
    vector<uint8_t> max_order(max_n, -1);
    vector<bool> active(max_n, true);

    for (uint8_t i = 0; i < max_n; i++) {
        uint8_t max_index = 0;

        while (!active[max_index]) {
            max_index++;
        }

        uint8_t max = (*params)[max_index];

        for (uint8_t j = max_index + 1; j < max_n; j++) {
            if (!active[j]) {
                continue;
            }

            if ((*params)[j] > max) {
                max = (*params)[j];
                max_index = j;
            }
        }

        max_order[i] = max_index;
        active[max_index] = false;
    }

    (*params) += max_n;
    return max_order;
}

inline StructuredPile* nn_decode_drop_ids(float** params) {
    StructuredPile* drop_ids = new StructuredPile("Drop ids");
    float* p_current = *params;

    for (unsigned i = 0; i < 4; i++) {
        uint8_t max_index = 0;
        float max = *(p_current++);

        for (unsigned mi = 1; mi < special_min_id + 1; mi++, p_current++) {
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

/*
 * Data format for prioritising action
 */
inline vector<vector<uint8_t>> nn_decode_drop_ids_list(float** params) {
    vector<vector<uint8_t>> result(4, vector<uint8_t>());

    for (unsigned i = 0; i < 4; i++) {
        result[i] = nn_decode_int_one_of_n_list(params, special_min_id);
    }

    return result;
}

#endif // NN_ENCODING_H
