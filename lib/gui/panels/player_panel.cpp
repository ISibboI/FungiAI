#include "player_panel.hpp"

#include <QGridLayout>
#include <QString>

PlayerPanel::PlayerPanel(Player* player, bool p1) :
	QGroupBox(QString::fromStdString(player->get_name())),
	display_panel(&player->get_display(), QString::fromStdString("Display")),
	hand_panel(&player->get_hand(), QString::fromStdString("Hand")),
	player(player) 
{
	QGridLayout* layout = new QGridLayout;

	layout->addWidget(&display_panel, 0, p1 ? 1 : 0);
	layout->addWidget(&hand_panel, 0, p1 ? 0 : 1);

	setLayout(layout);
}

PlayerPanel::~PlayerPanel() {}

void PlayerPanel::update() {
	display_panel.update();
}