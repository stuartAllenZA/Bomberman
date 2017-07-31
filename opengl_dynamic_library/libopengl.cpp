#include "libopengl.hpp"

extern "C" void	init() {
	std::cout << "OpenGl Renderer constructed" << std::endl;
}

extern "C" void	handleInput(int	gameInput) {
	gameInput = 0;
}

extern "C" void	updateGameData() {
}

extern "C" void render(Game &game) {
	std::vector<Character>::iterator begin;
	std::vector<Character> enemies = game.getEnemies();
	for (begin = enemies.begin(); begin < enemies.end(); begin++) {
		std::pair<int, int> xy = begin->getXY();
		// openGLRender(xy.first, xy.second, 'E');
		xy.first = 0;
	}
	
}

extern "C" void	destroy() {
	// any opengl destruction can be triggered here
}

