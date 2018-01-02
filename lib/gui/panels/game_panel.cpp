#include "game_panel.hpp"

#include <QGridLayout>

GamePanel::GamePanel(Game* game) :
	game(game),
	p1_panel(&game->get_p1(), true),
	p2_panel(&game->get_p2(), false),
	forest_panel(&game->get_forest())
{
	QGridLayout* game_view_layout = new QGridLayout;

	game_view_layout->addWidget(&p1_panel, 0, 0);
	game_view_layout->addWidget(&forest_panel, 0, 1);
	game_view_layout->addWidget(&p2_panel, 0, 2);

	QGridLayout* layout = new QGridLayout;
	layout->addLayout(game_view_layout, 0, 0, 1, 10, Qt::AlignTop);
	setLayout(layout);
}

GamePanel::~GamePanel() {}

void GamePanel::update() {
	p1_panel.update();
	p2_panel.update();
	forest_panel.update();
}