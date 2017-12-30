#include "gui/main_window.hpp"

using namespace nana;

int main() {
	Game game;
	MainWindow main_window(&game);

	exec();
	return 0;
}