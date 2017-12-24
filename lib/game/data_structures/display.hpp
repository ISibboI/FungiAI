#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "structured_pile.hpp"

class Display : public StructuredPile {
public:
	Display(const string& name);

	unsigned count_points() const;
	unsigned effective_mushroom_count() const;
};

#endif