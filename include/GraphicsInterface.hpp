#ifndef INCLUDE_GRAPHICS_INTERFACE_HPP_
#define INCLUDE_GRAPHICS_INTERFACE_HPP_

#include "../opengl_dynamic_library/include/Window.hpp"

class IGraphics {
	public:
		virtual void 	init(...)=0;
		virtual void 	handleInput(...)=0;
		virtual void 	updateGameData(...)=0;
		virtual void	addToRenderBuff(...)=0;
		virtual void 	render(...)=0;
		virtual void 	destroy(...)=0;
		virtual 		~IGraphics()=0;
};

#endif

