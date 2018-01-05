#ifndef GAME_PANEL_HPP
#define GAME_PANEL_HPP

#include "gui/panels/player_panel.hpp"
#include "gui/panels/forest_panel.hpp"
#include "game/game.hpp"
#include "game/run/controller.hpp"
#include "game/actions/actions.hpp"

#include <QWidget>
#include <QPushButton>
#include <QScrollArea>

enum GuiState {
	READY = 1,
	DISCARD_1 = 2,
	DISCARD_2 = 3,
	DISCARD_3 = 4,
	DISCARD_4 = 5,
	ACTION_PICK = 11,
	ACTION_PICK_DECAY = 12,
	ACTION_COOK = 13,
	ACTION_SELL = 14,
	ACTION_PLACE_PAN = 15,
	FINISHED = 100
};

class GamePanel : public QWidget {
	Q_OBJECT

private:
	PlayerPanel p1_panel;
	PlayerPanel p2_panel;
	ForestPanel forest_panel;
	QScrollArea* game_scroll_area;
	QWidget* game_scroll_widget;

	QPushButton action_pick_button;
	QPushButton action_pick_decay_button;
	QPushButton action_cook_button;
	QPushButton action_sell_button;
	QPushButton action_place_pan_button;
	QPushButton confirm_button;

	QLabel gui_state_label;
	QLabel action_target_label;
	QLabel action_consequence_label;
	GuiState gui_state;
	uint8_t target;
	bool current_player;

	Game* game;
	Controller* enemy;

	void game_finished_actions();

private slots:
	void handle_pick_button();
	void handle_pick_decay_button();
	void handle_cook_button();
	void handle_sell_button();
	void handle_place_pan_button();
	void handle_confirm_button();
	void handle_card_id_selected(uint8_t id);

public:
	GamePanel(Game* game, Controller* enemy);
	~GamePanel() override = default;

	void update_game_state();
};

#endif