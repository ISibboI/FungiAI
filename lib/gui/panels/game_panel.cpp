#include "game_panel.hpp"

#include <QGridLayout>

GamePanel::GamePanel(Game* game) :
	game(game),
	p1_panel(&game->get_p1(), true),
	p2_panel(&game->get_p2(), false),
	forest_panel(&game->get_forest()),
	action_pick_button(QString::fromStdString("Pick from forest")),
	action_pick_decay_button(QString::fromStdString("Pick decay pile")),
	action_cook_button(QString::fromStdString("Cook mushrooms")),
	action_sell_button(QString::fromStdString("Sell mushrooms")),
	action_place_pan_button(QString::fromStdString("Place pan")),
	confirm_button(QString::fromStdString("Confirm"))
{
	QGridLayout* game_view_layout = new QGridLayout;

	game_view_layout->addWidget(&p1_panel, 0, 0);
	game_view_layout->addWidget(&forest_panel, 1, 0);
	game_view_layout->addWidget(&p2_panel, 2, 0);

	QGridLayout* game_controls_layout = new QGridLayout;

	game_controls_layout->addWidget(&action_pick_button, 0, 0);
	game_controls_layout->addWidget(&action_pick_decay_button, 0, 1);
	game_controls_layout->addWidget(&action_cook_button, 0, 2);
	game_controls_layout->addWidget(&action_sell_button, 0, 3);
	game_controls_layout->addWidget(&action_place_pan_button, 0, 4);
	game_controls_layout->addWidget(&confirm_button, 0, 5);

	QGridLayout* layout = new QGridLayout;
	layout->addLayout(game_view_layout, 0, 0, 1, 1, Qt::AlignTop);
	layout->addLayout(game_controls_layout, 1, 0, 1, 1, Qt::AlignTop);
	setLayout(layout);
}

GamePanel::~GamePanel() {}

void GamePanel::update() {
	p1_panel.update();
	p2_panel.update();
	forest_panel.update();
}