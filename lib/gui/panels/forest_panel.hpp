#ifndef FOREST_PANEL_HPP
#define FOREST_PANEL_HPP

#include "game/forest.hpp"
#include "structured_pile_panel.hpp"

#include <QGroupBox>

class ForestPanel : public QGroupBox {
	Q_OBJECT

private:
	StructuredPilePanel discard_pile_panel;

	Forest* forest;

public:
	ForestPanel(Forest* forest);
	~ForestPanel();

	void update();
};

#endif