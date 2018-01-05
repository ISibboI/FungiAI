#include "gui/main_window.hpp"
#include "game/run/random_controller.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication q_application(argc, argv);

	spdlog::stdout_logger_st("DiscardAction");
    spdlog::stdout_logger_st("PickAction");
    spdlog::stdout_logger_st("PickDecayAction");
    spdlog::stdout_logger_st("CookMushroomsAction");
    spdlog::stdout_logger_st("SellMushroomsAction");
    spdlog::stdout_logger_st("PlacePanAction");
    spdlog::stdout_logger_st("RandomController");
    spdlog::stdout_logger_st("EvolutionalOptimization");
    spdlog::stdout_logger_st("PercentileReproductionStrategy");
    spdlog::stdout_logger_st("CompleteRankingAlgorithm");
    spdlog::stdout_logger_st("Forest");
    spdlog::stdout_logger_st("ReproductionStrategy");

	Game game;
	mt19937_64 random_engine;
	game.initialize(random_engine);

    RandomController controller("Enemy", 55624567);

	MainWindow main_window(&game, &controller);

	return q_application.exec();
}