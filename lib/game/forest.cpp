#include "forest.hpp"

Forest::Forest() : discard_pile("Discard Pile") {}

void Forest::initialize() {
	draw_pile.clear();
	forest.clear();
	decay_pile.clear();
	discard_pile.clear();
}