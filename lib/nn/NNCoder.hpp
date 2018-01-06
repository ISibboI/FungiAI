#ifndef NN_ENCODER_HPP
#define NN_ENCODER_HPP

#include "game/game.hpp"
#include "game/actions/CombinedAction.hpp"
#include "game/cards/card_information.hpp"

#include <vector>

using namespace std;

class NNCoder {
private:
	static void encode(unsigned i, unsigned max_value, float** output);
    static void encode(vector<uint8_t>& ids, unsigned size, float** output);
    static void encode(StructuredPile& structured_pile, bool hidden, float** output);
    static void encode(Forest& forest, float** output);
    static void encode(Player& player, bool hidden, float** output);

    static void decode_priority_permutation(float** begin, unsigned length, vector<uint8_t>& output);

    NNCoder() = default;
    ~NNCoder() = default;

    static size_t nn_input_size;

public:
    static void encode(Game& game, bool p1, float* nn_input);
    static void decode(float* nn_output, CombinedAction& output);

    static size_t get_nn_input_size() {
        if (nn_input_size == (size_t) -1) {
            Game game;
            vector<float> big_vector(100000, -1);
            encode(game, true, big_vector.data());
            nn_input_size = 0;
            while (big_vector[nn_input_size] != -1) {
                nn_input_size++;
            }
        }

        return nn_input_size;
    }
    static constexpr size_t get_nn_output_size() { return 5 + 8 + 20 + 9 + 9; }
};

#endif