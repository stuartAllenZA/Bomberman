#include <GraphicsHandler.hpp>

GraphicsHandler::GraphicsHandler() {}

GraphicsHandler::~GraphicsHandler() {
	typedef void	(*destroy_t)();
	destroy_t	destroy = (destroy_t) dlsym(_handle, "destroy");
	destroy();
}

GraphicsHandler::GraphicsHandler(std::string name) {
	std::cout
		<< "Graphics Handler Constructed"
		<< std::endl
		;
	_handle = dlopen(name.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!_handle)
		throw Exceptions::UndefinedObject();
	else {
		typedef void (*init_t)();
		init_t init = (init_t) dlsym(_handle, "init");
		if (!init)
			throw Exceptions::UndefinedSymbol();
		else (*init)();
	}
}

void		GraphicsHandler::getGameEvents(Game &game) {
	typedef void (*getGameEvents_t)(int);
	getGameEvents_t getGameEvents = (getGameEvents_t) dlsym(_handle, "getGameEvents");
	getGameEvents(Game.gameInput);
}

void	GraphicsHandler::renderGraphics(Game &game) {
}

