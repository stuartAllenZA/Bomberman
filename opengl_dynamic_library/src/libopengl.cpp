//#include <libopengl.hpp>
//#include <Window.hpp>
#include "../include/Window.hpp"
#include "../include/libopengl.hpp"

//Libopengl::Libopengl() {
//	std::cout << "Lib constructed\n";
//	//_window = new Window;
//}

extern "C" Window*	init() {
    Window* test = new Window;
    //Test->init();
	return (test);
	//TODO delete window
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

}


//Libopengl::~Libopengl() {
//	std::cout << "lib Destructed\n";
//}

