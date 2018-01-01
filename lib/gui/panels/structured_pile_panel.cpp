#include "structured_pile_panel.hpp"
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
	for (auto card_panel : card_panels) {
		delete card_panel;
	}

	card_panels.clear();

	QGridLayout* layout = new QGridLayout;
	int currentHeight = 0;

	for (uint8_t id = 0; id < CardInformation::get_all_cards().size(); id++) {
		unsigned count = structured_pile->card_count(id);

		if (count > 0) {
			CardPanel* card_panel = new CardPanel(id);

			layout->addWidget(card_panel, currentHeight++, 0);
			card_panels.push_back(card_panel);
		}
	}

	setLayout(layout);
}