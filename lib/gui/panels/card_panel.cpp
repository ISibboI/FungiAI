#include "card_panel.hpp"
#include "gui/util/gui_util.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QString>

CardPanel::CardPanel(uint8_t id) :
	QLabel(QString::fromStdString(CardInformation::get_card(id).name)),
	id(id)
{
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

CardPanel::~CardPanel() {}

MultiCardPanel::MultiCardPanel(uint8_t id, uint8_t count) :
	id(id),
	count(count)
{
	QGridLayout* layout = new QGridLayout;
	layout->setSpacing(0);
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0, 0);

	for (unsigned i = 0; i < count; i++) {
		layout->addWidget(new CardPanel(id), i, 0);
	}

	setLayout(layout);
}

MultiCardPanel::~MultiCardPanel() {
	GuiUtil::replace_layout(this, 0);
}