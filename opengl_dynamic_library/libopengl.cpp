#include "libopengl.hpp"

extern "C" void	init() {
	std::cout << "OpenGl Renderer constructed" << std::endl;
}

extern "C" void	handleInput(int	gameInput) {
	gameInput = 0;
}

extern "C" void	updateGameData() {
}

extern "C" void render() {
	// vector<game.enemies>::iterator begin;
	// for (begin = game.begin();begin < game.end(); begin++) {
	//	openGLRender(begin.x, begin.y, 'E');
	// }
	//
}

extern "C" void	destroy() {
	// any opengl destruction can be triggered here
}

