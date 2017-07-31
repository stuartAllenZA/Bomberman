#include "libopengl.hpp"

extern "C" void	init() {
	std::cout << "OpenGl Renderer constructed" << std::endl;
}

extern "C" void	handleInput(int	gameInput) {
	gameInput = 0;
}

extern "C" void	updateGameData() {
}

extern "C" void addToRenderBuff(int x, int y, char symbol) {
	(void)x;
	(void)y;
	(void)symbol;
}

extern "C" void render() {

}

extern "C" void	destroy() {
	// any opengl destruction can be triggered here
}

