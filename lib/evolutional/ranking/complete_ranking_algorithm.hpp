#ifndef COMPLETE_RANKING_ALGORITHM_HPP
#define COMPLETE_RANKING_ALGORITHM_HPP

#include "ranking_algorithm.hpp"
#include "spdlog.h"

using namespace std;

class CompleteRankingAlgorithm : public RankingAlgorithm {
private:
	shared_ptr<spdlog::logger> logger;

public:
	CompleteRankingAlgorithm();
	~CompleteRankingAlgorithm() override = default;

	void rank(vector<EvolutionalNNController*>& population, mt19937_64& random_engine) override;
};

#endif