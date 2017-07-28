#ifndef INCLUDE_GRAPHICS_HANDLER_HPP_
#define INCLUDE_GRAPHICS_HANDLER_HPP_

#include <string>
#include <iostream>
#include <dlfcn.h>
#include <GameClass.hpp>

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

