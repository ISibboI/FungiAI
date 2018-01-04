#ifndef GAME_PANEL_HPP
#define GAME_PANEL_HPP

#include "gui/panels/player_panel.hpp"
#include "gui/panels/forest_panel.hpp"
#include "game/game.hpp"

#include <QWidget>
#include <QPushButton>

class GamePanel : public QWidget {
	Q_OBJECT

private:
	PlayerPanel p1_panel;
	PlayerPanel p2_panel;
	ForestPanel forest_panel;

	QPushButton action_pick_button;
	QPushButton action_pick_decay_button;
	QPushButton action_cook_button;
	QPushButton action_sell_button;
	QPushButton action_place_pan_button;
	QPushButton confirm_button;

	Game* game;

public:
	GamePanel(Game* game);
	~GamePanel();

	void update();
};

#endif