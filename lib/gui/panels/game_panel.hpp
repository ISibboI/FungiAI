#ifndef GAME_PANEL_HPP
#define GAME_PANEL_HPP

#include "gui/panels/player_panel.hpp"
#include "gui/panels/forest_panel.hpp"
#include "game/game.hpp"

#include <QWidget>

class GamePanel : public QWidget {
	Q_OBJECT

private:
	PlayerPanel p1_panel;
	PlayerPanel p2_panel;
	ForestPanel forest_panel;

	Game* game;

public:
	GamePanel(Game* game);
	~GamePanel();

	void update();
};

#endif