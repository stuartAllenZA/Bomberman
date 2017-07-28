#ifndef INCLUDE_GRAPHICS_HANDLER_HPP
#define INCLUDE_GRAPHICS_HANDLER_HPP

#include <string>
#include <dlfcn.h>
#include <Game.hpp>

class GraphicsHandler {
	public:
		GraphicsHandler();
		~GraphicsHandler();
		GraphicsHandler(std::string);
		void	init();
		void	getGameEvents(Game&);
		void	updateGameData();
		void	renderGraphics(Game&);
	
	private:
		void	*_handle;
};

#endif

