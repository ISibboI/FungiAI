#include "vector_panel.hpp"
#include "gui/util/gui_util.hpp"

#include <QGridLayout>
#include <QLabel>

VectorPanel::VectorPanel(vector<uint8_t>* cards, const QString& title) :
	QGroupBox(title),
	cards(cards),
	delimiter(-1)
{
	update();
}

VectorPanel::~VectorPanel() {}

void VectorPanel::update() {
	QGridLayout* layout = new QGridLayout;
	
	int currentHeight = 0;

	for (uint8_t id : *cards) {
		if (currentHeight == delimiter) {
			QLabel* delimiter_label = new QLabel(QString::fromStdString("------------------"));

			layout->setRowStretch(currentHeight, 1);
			layout->addWidget(delimiter_label, currentHeight++, 0, 1, 1, Qt::AlignTop);
		}

		CardPanel* card_panel = new CardPanel(id);

		layout->setRowStretch(currentHeight, 1);
		layout->addWidget(card_panel, currentHeight++, 0, 1, 1, Qt::AlignTop);
	}

	GuiUtil::replace_layout(this, layout);
}

void VectorPanel::set_delimiter(int delimiter) {
	this->delimiter = delimiter;
}