#ifndef RANDOM_CONTROLLER_HPP
#define RANDOM_CONTROLLER_HPP

#include "evolutional_controller.hpp"
#include "spdlog.h"

#include <random>
#include <memory>

using namespace std;

class RandomController : public EvolutionalController {
private:
	mt19937_64 random_engine;
	shared_ptr<spdlog::logger> logger;

	vector<uint8_t> random_sequence(uint8_t min, uint8_t count);

public:
	RandomController(const string& name, unsigned seed);
	virtual ~RandomController();

	virtual void do_turn(Player& me, Player& enemy, Forest& forest);
	virtual RandomController* make_baby(mt19937_64& random_engine) const;
};

#endif