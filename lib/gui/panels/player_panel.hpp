#ifndef PLAYER_PANEL_HPP
#define PLAYER_PANEL_HPP

#include "game/player.hpp"
#include "structured_pile_panel.hpp"

#include <QGroupBox>

class PlayerPanel : public QGroupBox {
	Q_OBJECT

private:
	StructuredPilePanel display_panel;
	StructuredPilePanel hand_panel;

	Player* player;

public:
	PlayerPanel(Player* player, bool p1);
	~PlayerPanel();

	void update();
};

#endif