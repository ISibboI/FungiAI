#include "game_panel.hpp"

#include <QGridLayout>

GamePanel::GamePanel(Game* game) :
	game(game),
	p1(&game->get_p1(), true),
	p2(&game->get_p2(), false)
{
	QGridLayout* layout = new QGridLayout;

	layout->addWidget(&p1, 0, 0);
	layout->addWidget(&p2, 0, 2);

	setLayout(layout);
}

GamePanel::~GamePanel() {}

void GamePanel::update() {
	p1.update();
	p2.update();
}