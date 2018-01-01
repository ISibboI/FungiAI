#ifndef GAME_PANEL_HPP
#define GAME_PANEL_HPP

#include "gui/panels/player_panel.hpp"
#include "game/game.hpp"

#include <QWidget>

class GamePanel : public QWidget {
	Q_OBJECT

private:
	PlayerPanel p1;
	PlayerPanel p2;

	Game* game;

public:
	GamePanel(Game* game);
	~GamePanel();

	void update();
};

#endif