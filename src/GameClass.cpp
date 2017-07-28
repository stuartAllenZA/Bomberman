#include <GameClass.hpp>

Game::Game() {
	std::cout << "Game Constructed" << std::endl;
	GraphicsHandler		graphics;
	graphics.init();
}

void	Game::run() {
	for (;;) {
		// getInput
		// updateGameState
		// render
	}
}
