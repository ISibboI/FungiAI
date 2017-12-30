#ifndef NN_ENCODER_HPP
#define NN_ENCODER_HPP

#include "game/game.hpp"

#include <vector>

using namespace std;

class NNEncoder {
private:
	void encode(unsigned i, unsigned max_value, vector<float>& v);
	void encode(vector<uint8_t>& ids, unsigned size, vector<float>& v);
	void encode(StructuredPile& structured_pile, bool hidden, vector<float>& v);
	void encode(Forest& forest, vector<float>& v);
	void encode(Player& player, bool hidden, vector<float>& v);

public:
	NNEncoder();
	~NNEncoder();

	void encode(Game& game, bool p1, vector<float>& v);
};

#endif