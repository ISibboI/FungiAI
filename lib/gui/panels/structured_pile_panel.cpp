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
	unsigned current_col = 0;

	for (uint8_t id = 0; id < CardInformation::get_all_cards().size(); id++) {
		unsigned count = structured_pile->card_count(id);

		if (count > 0) {
			MultiCardPanel* card_panel = new MultiCardPanel(id, count);
			layout->setColumnStretch(current_col, 0);
			card_panel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
			layout->addWidget(card_panel, 0, current_col++, 1, 1, Qt::AlignLeft | Qt::AlignTop);
		}
	}

	if (current_col > 0) {
		layout->setColumnStretch(current_col - 1, 1);
	}

	GuiUtil::replace_layout(this, layout);
}