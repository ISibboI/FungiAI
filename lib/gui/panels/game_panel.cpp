#include "game_panel.hpp"
#include "game/cards/card_information.hpp"

#include <QGridLayout>
#include <stdexcept>

GamePanel::GamePanel(Game* game) :
	game(game),
	p1_panel(&game->get_p1(), true, this),
	p2_panel(&game->get_p2(), false, this),
	forest_panel(&game->get_forest(), this),
	action_pick_button(QString::fromStdString("Pick from forest")),
	action_pick_decay_button(QString::fromStdString("Pick decay pile")),
	action_cook_button(QString::fromStdString("Cook mushrooms")),
	action_sell_button(QString::fromStdString("Sell mushrooms")),
	action_place_pan_button(QString::fromStdString("Place pan")),
	confirm_button(QString::fromStdString("Confirm")),
	gui_state_label(QString::fromStdString("Ready")),
	gui_state(GuiState::READY),
	current_player(true)
{
	QGridLayout* game_view_layout = new QGridLayout;

	game_view_layout->addWidget(&p1_panel, 0, 0);
	game_view_layout->addWidget(&forest_panel, 1, 0);
	game_view_layout->addWidget(&p2_panel, 2, 0);
	game_scroll_widget.setLayout(game_view_layout);

	game_scroll_area.setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
	game_scroll_area.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	game_scroll_area.setWidgetResizable(true);
	game_scroll_area.setWidget(&game_scroll_widget);

	QGridLayout* game_controls_layout = new QGridLayout;

	game_controls_layout->addWidget(&action_pick_button, 0, 0);
	game_controls_layout->addWidget(&action_pick_decay_button, 0, 1);
	game_controls_layout->addWidget(&action_cook_button, 0, 2);
	game_controls_layout->addWidget(&action_sell_button, 0, 3);
	game_controls_layout->addWidget(&action_place_pan_button, 0, 4);
	game_controls_layout->addWidget(&confirm_button, 0, 5);

	QGridLayout* turn_information_layout = new QGridLayout;

	turn_information_layout->addWidget(&gui_state_label, 0, 0);
	turn_information_layout->addWidget(&action_target_label, 0, 1);
	turn_information_layout->addWidget(&action_consequence_label, 0, 2);

	QGridLayout* layout = new QGridLayout;
	layout->addWidget(&game_scroll_area, 0, 0, 1, 1, Qt::AlignTop);
	layout->addLayout(game_controls_layout, 1, 0, 1, 1, Qt::AlignBottom);
	layout->addLayout(turn_information_layout, 2, 0, 1, 1, Qt::AlignBottom);

	layout->setRowStretch(0, 1);
	layout->setRowStretch(1, 0);
	layout->setRowStretch(2, 0);
	setLayout(layout);

	connect(&action_pick_button, SIGNAL(released()), this, SLOT(handle_pick_button()));
	connect(&action_pick_decay_button, SIGNAL(released()), this, SLOT(handle_pick_decay_button()));
	connect(&action_cook_button, SIGNAL(released()), this, SLOT(handle_cook_button()));
	connect(&action_sell_button, SIGNAL(released()), this, SLOT(handle_sell_button()));
	connect(&action_place_pan_button, SIGNAL(released()), this, SLOT(handle_place_pan_button()));
	connect(&confirm_button, SIGNAL(released()), this, SLOT(handle_confirm_button()));

	adjustSize();
}

GamePanel::~GamePanel() {}

void GamePanel::update() {
	p1_panel.update();
	p2_panel.update();
	forest_panel.update();
}

void GamePanel::handle_pick_button() {
	if (gui_state >= GuiState::DISCARD_1 && gui_state <= GuiState::DISCARD_4) {return;}
	gui_state = GuiState::ACTION_PICK;
	gui_state_label.setText(QString::fromStdString("Pick mushroom"));
	target = 255;
}

void GamePanel::handle_pick_decay_button() {
	if (gui_state >= GuiState::DISCARD_1 && gui_state <= GuiState::DISCARD_4) {return;}
	gui_state = GuiState::ACTION_PICK_DECAY;
	gui_state_label.setText(QString::fromStdString("Pick decay pile"));
	target = 255;
}

void GamePanel::handle_cook_button() {
	if (gui_state >= GuiState::DISCARD_1 && gui_state <= GuiState::DISCARD_4) {return;}
	gui_state = GuiState::ACTION_COOK;
	gui_state_label.setText(QString::fromStdString("Cook mushrooms"));
	target = 255;
}

void GamePanel::handle_sell_button() {
	if (gui_state >= GuiState::DISCARD_1 && gui_state <= GuiState::DISCARD_4) {return;}
	gui_state = GuiState::ACTION_SELL;
	gui_state_label.setText(QString::fromStdString("Sell mushrooms"));
	target = 255;
}

void GamePanel::handle_place_pan_button() {
	if (gui_state >= GuiState::DISCARD_1 && gui_state <= GuiState::DISCARD_4) {return;}
	gui_state = GuiState::ACTION_PLACE_PAN;
	gui_state_label.setText(QString::fromStdString("Place pan"));
	target = 255;
}

void GamePanel::handle_confirm_button() {
	switch (gui_state) {
	case GuiState::DISCARD_1:
	case GuiState::DISCARD_2:
	case GuiState::DISCARD_3:
	case GuiState::DISCARD_4: {
		if (target == 255) {return;}

		DiscardAction discard_action({target});
		if (!discard_action.execute(game->get_player(current_player), game->get_forest())) {return;}
		gui_state = (GuiState) (gui_state - 1); // TODO How much cards were actually discarded?
		if (gui_state != GuiState::READY) {
			gui_state_label.setText(QString::fromStdString("Discard %1 cards").arg(gui_state - GuiState::READY));
			action_target_label.setText(QString());
			target = 255;
			action_consequence_label.setText(QString());
			update();
			return;
		}

		break;
	}
	case GuiState::ACTION_PICK: {
		if (target == 255) {return;}

		uint8_t real_id = 255;
		for (uint8_t i = 0; i < game->get_forest().get_forest().size(); i++) {
			if (target == game->get_forest().get_forest()[i]) {
				real_id = i;
				break;
			}
		}
		if (real_id == 255) {return;}

		IgnoreDiscardAction ignore_discard_action;
		PickAction pick_action({real_id}, &ignore_discard_action);
		if (!pick_action.execute(game->get_player(current_player), game->get_forest())) {return;}
		gui_state = (GuiState) (GuiState::READY + ignore_discard_action.get_discard_count());
		if (gui_state != GuiState::READY) {
			gui_state_label.setText(QString::fromStdString("Discard %1 cards").arg(ignore_discard_action.get_discard_count()));
			action_target_label.setText(QString());
			target = 255;
			action_consequence_label.setText(QString());
			update();
			return;
		}

		break;
	}
	case GuiState::ACTION_PICK_DECAY: {
		IgnoreDiscardAction ignore_discard_action;
		PickDecayAction pick_decay_action(&ignore_discard_action);
		if (!pick_decay_action.execute(game->get_player(current_player), game->get_forest())) {return;}
		gui_state = (GuiState) (GuiState::READY + ignore_discard_action.get_discard_count());
		if (gui_state != GuiState::READY) {
			gui_state_label.setText(QString::fromStdString("Discard %1 cards").arg(ignore_discard_action.get_discard_count()));
			action_target_label.setText(QString());
			target = 255;
			action_consequence_label.setText(QString());
			update();
			return;
		}

		break;
	}
	case GuiState::ACTION_COOK: {
		if (target == 255) {return;}

		CookMushroomsAction cook_mushrooms_action({target});
		if (!cook_mushrooms_action.execute(game->get_player(current_player), game->get_forest())) {return;}
		break;
	}
	case GuiState::ACTION_SELL: {
		if (target == 255) {return;}

		SellMushroomsAction sell_mushrooms_action({target});
		if (!sell_mushrooms_action.execute(game->get_player(current_player), game->get_forest())) {return;}
		break;
	}
	case GuiState::ACTION_PLACE_PAN: {
		PlacePanAction place_pan_action;
		if (!place_pan_action.execute(game->get_player(current_player), game->get_forest())) {return;}
		break;
	}
	default:
		throw runtime_error("Unknown state");
	}

	gui_state = GuiState::READY;
	gui_state_label.setText(QString::fromStdString("Ready"));
	action_target_label.setText(QString());
	target = 255;
	action_consequence_label.setText(QString());
	game->post_turn_actions();
	update();
	current_player = !current_player;
}

void GamePanel::handle_card_id_selected(uint8_t id) {
	if (gui_state != GuiState::READY) {
		target = id;
		action_target_label.setText(QString::fromStdString(CardInformation::get_card(id).name));
	}
}