#include "card_panel.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QString>

CardPanel::CardPanel(uint8_t id) :
	QLabel(QString::fromStdString(CardInformation::get_card(id).name)),
	id(id)
{
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	/*QLabel* content = new QLabel(QString::fromStdString(CardInformation::get_card(id).name));
	content->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	QGridLayout* layout = new QGridLayout;
	layout->setSpacing(0);
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0, 0);

	layout->addWidget(content, 0, 0, Qt::AlignTop);

	setLayout(layout);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);*/
}

CardPanel::~CardPanel() {}