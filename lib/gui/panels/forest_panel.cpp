#include "forest_panel.hpp"

#include <QGridLayout>

ForestPanel::ForestPanel(Forest* forest) :
	QGroupBox(QString::fromStdString("Forest")),
	discard_pile_panel(&forest->get_discard_pile(), QString::fromStdString("Discard pile")),
	forest(forest)
{
	QGridLayout* layout = new QGridLayout;

	layout->addWidget(&discard_pile_panel, 0, 0);

	setLayout(layout);
}

ForestPanel::~ForestPanel() {}

void ForestPanel::update() {
	discard_pile_panel.update();
}