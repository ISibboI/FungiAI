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

void CardPanel::mouseReleaseEvent(QMouseEvent* event) {
	emit released(id);
}


MultiCardPanel::MultiCardPanel(uint8_t id, uint8_t count, QWidget* receiver) :
	id(id),
	count(count)
{
	QGridLayout* frame_layout = new QGridLayout;
	frame_layout->setSpacing(0);
	frame_layout->setMargin(0);
	frame_layout->setContentsMargins(0, 0, 0, 0);

	for (unsigned i = 0; i < count; i++) {
		CardPanel* card_panel = new CardPanel(id);
		frame_layout->addWidget(card_panel, i, 0);
		connect(card_panel, SIGNAL(released(uint8_t)), receiver, SLOT(handle_card_id_selected(uint8_t)));
	}

	q_frame.setFrameShape(QFrame::StyledPanel);
	q_frame.setFrameShadow(QFrame::Raised);
	q_frame.setLayout(frame_layout);

	QGridLayout* layout = new QGridLayout;
	layout->setSpacing(0);
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(&q_frame, 0, 0);
	setLayout(layout);
}

MultiCardPanel::~MultiCardPanel() {
	GuiUtil::replace_layout(&q_frame, 0);
	GuiUtil::replace_layout(this, 0);
}