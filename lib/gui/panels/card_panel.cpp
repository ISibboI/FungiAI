#include "card_panel.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QString>

CardPanel::CardPanel(uint8_t id) :
	id(id)
{
	QGridLayout* layout = new QGridLayout;

	layout->addWidget(new QLabel(QString::fromStdString(CardInformation::get_card(id).name)));

	setLayout(layout);
}

CardPanel::~CardPanel() {}