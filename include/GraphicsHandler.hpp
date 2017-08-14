#ifndef INCLUDE_GRAPHICS_HANDLER_HPP
#define INCLUDE_GRAPHICS_HANDLER_HPP

#include <string>
#include <dlfcn.h>
#include "Game.hpp"
#include "../opengl_dynamic_library/include/Window.hpp"

class GraphicsHandler {
	public:
		GraphicsHandler();
		~GraphicsHandler();
		GraphicsHandler(std::string);
		void	init();
		int		getUserInput();
		void	updateGameData();
		void	loadGameToRenderBuff(Game &game);
		void	addToRenderBuff(int x, int y, char symbol);
		void	render();
	
	private:
		void	*_handle;
		Window	*_window;
};

#endif

