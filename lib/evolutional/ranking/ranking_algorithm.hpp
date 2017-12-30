#ifndef RANKING_ALGORITHM_HPP
#define RANKING_ALGORITHM_HPP

#include "game/run/game_runner.hpp"
#include "evolutional/evolutional_controller.hpp"

#include <vector>
#include <random>

using namespace std;

class RankingAlgorithm {
private:
	GameRunner game_runner;

protected:
	GameRunner& get_game_runner();

public:
	RankingAlgorithm();
	~RankingAlgorithm();

	virtual void rank(vector<EvolutionalController*>& population, mt19937_64& random_engine) = 0;

	void sort_by(vector<EvolutionalController*>& population, vector<unsigned>& points) const;
};

#endif