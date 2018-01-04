#ifndef FOREST_PANEL_HPP
#define FOREST_PANEL_HPP

#include "game/forest.hpp"
#include "structured_pile_panel.hpp"
#include "vector_panel.hpp"

#include <QGroupBox>
#include <QLabel>

class ForestPanel : public QGroupBox {
	Q_OBJECT

private:
	QLabel draw_pile_label;
	VectorPanel forest_panel;
	VectorPanel decay_pile_panel;
	StructuredPilePanel discard_pile_panel;

	Forest* forest;

public:
	ForestPanel(Forest* forest, QWidget* receiver);
	~ForestPanel();

	void update();
};

#endif