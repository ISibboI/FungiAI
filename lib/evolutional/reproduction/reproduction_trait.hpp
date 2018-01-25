#ifndef EVOLUTIONAL_CONTROLLER_HPP
#define EVOLUTIONAL_CONTROLLER_HPP

#include "game/run/controller.hpp"

#include <random>

using namespace std;

template<typename T>
class ReproductionTrait {
public:
	ReproductionTrait() = default;
	virtual ~ReproductionTrait() = default;

	virtual T* make_baby(mt19937_64& random_engine, double randomness) const = 0;
};

#endif