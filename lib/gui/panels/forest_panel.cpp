#include "forest_panel.hpp"

#include <QGridLayout>

ForestPanel::ForestPanel(Forest* forest) :
	QGroupBox(QString::fromStdString("Forest")),
	draw_pile_label(QString::fromStdString("Draw pile: ")),
	forest_panel(&forest->get_forest(), QString::fromStdString("Forest")),
	decay_pile_panel(&forest->get_decay_pile(), QString::fromStdString("Decay pile")),
	discard_pile_panel(&forest->get_discard_pile(), QString::fromStdString("Discard pile")),
	forest(forest)
{
	QGridLayout* layout = new QGridLayout;

	layout->addWidget(&draw_pile_label, 0, 0, Qt::AlignTop);
	layout->addWidget(&forest_panel, 1, 0, Qt::AlignTop);
	layout->addWidget(&decay_pile_panel, 2, 0, Qt::AlignTop);
	layout->addWidget(&discard_pile_panel, 3, 0, Qt::AlignTop);

	forest_panel.set_delimiter(2);
	forest_panel.update();

	setLayout(layout);
}

ForestPanel::~ForestPanel() {}

void ForestPanel::update() {
	QString draw_pile_string = QString("Draw pile: ").arg(forest->get_draw_pile().size());
	draw_pile_label.setText(draw_pile_string);

	forest_panel.update();
	decay_pile_panel.update();
	discard_pile_panel.update();
}