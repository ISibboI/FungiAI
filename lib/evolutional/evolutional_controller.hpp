#ifndef EVOLUTIONAL_CONTROLLER_HPP
#define EVOLUTIONAL_CONTROLLER_HPP

#include "game/run/controller.hpp"

#include <random>

using namespace std;

class EvolutionalController : public Controller {
public:
	EvolutionalController(const string& name);
	virtual ~EvolutionalController();

	virtual EvolutionalController* make_baby(mt19937_64& random_engine) const = 0;
};

#endif