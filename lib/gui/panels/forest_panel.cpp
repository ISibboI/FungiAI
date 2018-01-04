#include "forest_panel.hpp"

#include <QGridLayout>

ForestPanel::ForestPanel(Forest* forest, QWidget* receiver) :
	QGroupBox(QString::fromStdString("Forest")),
	draw_pile_label(QString::fromStdString("Draw pile: %1").arg(forest->get_draw_pile().size())),
	forest_panel(&forest->get_forest(), QString::fromStdString("Forest"), receiver),
	decay_pile_panel(&forest->get_decay_pile(), QString::fromStdString("Decay pile"), receiver),
	discard_pile_panel(&forest->get_discard_pile(), QString::fromStdString("Discard pile"), receiver),
	forest(forest)
{
	QGridLayout* layout = new QGridLayout;

	layout->addWidget(&draw_pile_label, 0, 2, Qt::AlignTop | Qt::AlignRight);
	layout->addWidget(&forest_panel, 0, 1, Qt::AlignTop | Qt::AlignHCenter);
	layout->addWidget(&decay_pile_panel, 0, 0, Qt::AlignTop | Qt::AlignLeft);
	layout->addWidget(&discard_pile_panel, 1, 0, 1, 3, Qt::AlignBottom);

	forest_panel.set_delimiter(2);
	forest_panel.update();

	setLayout(layout);
}

ForestPanel::~ForestPanel() {}

void ForestPanel::update() {
	QString draw_pile_string = QString("Draw pile: %1").arg(forest->get_draw_pile().size());
	draw_pile_label.setText(draw_pile_string);

	forest_panel.update();
	decay_pile_panel.update();
	discard_pile_panel.update();
}