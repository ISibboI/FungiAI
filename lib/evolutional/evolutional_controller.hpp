#ifndef EVOLUTIONAL_CONTROLLER_HPP
#define EVOLUTIONAL_CONTROLLER_HPP

#include "game/run/controller.hpp"

#include <random>

using namespace std;

class EvolutionalController : public Controller {
public:
	explicit EvolutionalController(const string& name);
	~EvolutionalController() override = default;

	virtual EvolutionalController* make_baby(mt19937_64& random_engine) const = 0;
};

#endif