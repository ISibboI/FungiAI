#include "structured_pile_panel.hpp"
#include "gui/util/gui_util.hpp"
#include "game/cards/card_information.hpp"

#include <QGridLayout>

StructuredPilePanel::StructuredPilePanel(StructuredPile* structured_pile, const QString& title) :
	QGroupBox(title),
	structured_pile(structured_pile)
{
	update();
}

StructuredPilePanel::~StructuredPilePanel() {}

void StructuredPilePanel::update() {
	QGridLayout* layout = new QGridLayout;
	int currentHeight = 0;

	for (uint8_t id = 0; id < CardInformation::get_all_cards().size(); id++) {
		unsigned count = structured_pile->card_count(id);

		while (count-- > 0) {
			CardPanel* card_panel = new CardPanel(id);

			layout->setRowStretch(currentHeight, 1);
			layout->addWidget(card_panel, currentHeight++, 0, 1, 1, Qt::AlignLeft | Qt::AlignTop);
		}
	}

	GuiUtil::replace_layout(this, layout);
}