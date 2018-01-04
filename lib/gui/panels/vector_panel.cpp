#include "vector_panel.hpp"
#include "gui/util/gui_util.hpp"

#include <QGridLayout>
#include <QLabel>

VectorPanel::VectorPanel(vector<uint8_t>* cards, const QString& title, QWidget* receiver) :
	QGroupBox(title),
	cards(cards),
	delimiter(-1),
	receiver(receiver)
{
	update();
}

VectorPanel::~VectorPanel() {}

void VectorPanel::update() {
	QGridLayout* layout = new QGridLayout;
	
	unsigned current_col = 0;

	for (uint8_t id : *cards) {
		if (current_col == delimiter) {
			QLabel* delimiter_label = new QLabel(QString::fromStdString("  "));

			layout->setColumnStretch(current_col, 0);
			delimiter_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
			layout->addWidget(delimiter_label, 0, current_col++, Qt::AlignLeft | Qt::AlignTop);
		}

		CardPanel* card_panel = new CardPanel(id);

		layout->setColumnStretch(current_col, 0);
		card_panel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
		card_panel->setFrameShape(QFrame::StyledPanel);
		card_panel->setFrameShadow(QFrame::Raised);
		layout->addWidget(card_panel, 0, current_col++, Qt::AlignLeft | Qt::AlignTop);

		connect(card_panel, SIGNAL(released(uint8_t)), receiver, SLOT(handle_card_id_selected(uint8_t)));
	}

	if (current_col > 0) {
		layout->setColumnStretch(current_col - 1, 1);
	}

	GuiUtil::replace_layout(this, layout);
}

void VectorPanel::set_delimiter(int delimiter) {
	this->delimiter = delimiter;
}