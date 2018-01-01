#include "main_window.hpp"

#include <QGridLayout>

MainWindow::MainWindow(Game* game) :
	game_panel(game)
{
	QGridLayout* layout = new QGridLayout;

	layout->addWidget(&game_panel, 0, 0);

	setLayout(layout);

	setWindowTitle("Fungi");
	show();
}

MainWindow::~MainWindow() {}