#ifndef RANKING_ALGORITHM_HPP
#define RANKING_ALGORITHM_HPP

#include "game/run/game_runner.hpp"
#include "evolutional/EvolutionalNNController.hpp"

#include <vector>
#include <random>

using namespace std;

class RankingAlgorithm {
private:
	std::vector<GameRunner> game_runners;

protected:
	GameRunner& get_game_runner(size_t index);

public:
	RankingAlgorithm() = default;
	virtual ~RankingAlgorithm() = default;

	virtual void rank(vector<EvolutionalNNController*>& population, mt19937_64& random_engine) = 0;

	void sort_by(vector<EvolutionalNNController*>& population, vector<unsigned>& points) const;
};

#endif