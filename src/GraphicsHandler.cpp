#include <GraphicsHandler.hpp>

GraphicsHandler::GraphicsHandler() {}

GraphicsHandler::~GraphicsHandler() {
	typedef void	(*destroy_t)();
	destroy_t	destroy = (destroy_t) dlsym(_handle, "destroy");
	destroy();
}

GraphicsHandler::GraphicsHandler(std::string name) {
	if (name.length() > 0)
		_handle = dlopen(name.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!_handle)
		throw Exceptions::UndefinedObject();
	else {
		typedef Window* (*init_t);
		init_t init = (init_t) dlsym(_handle, "init");
		if (!init)
			throw Exceptions::UndefinedSymbol();
		else (_window = *init);
	}
	std::cout << "Graphics Handler " << name << " Constructed\n";
}

int		GraphicsHandler::getUserInput() {
	typedef int (*getGameEvents_t)();
	getGameEvents_t getGameEvents = (getGameEvents_t) dlsym(_handle, "getGameEvents");
	int input = getGameEvents();
	return input;
}

void		GraphicsHandler::loadGameToRenderBuff(Game &game) {
	std::vector<Character*>enemies = game.getEnemies();
//	std::vector<Character*>::iterator	enemy;
	Character	*player = game.getPlayer();
	std::pair<int, int> coords;
	int x, y;
	for (size_t i = 0; i < enemies.size(); i++) {
		coords = enemies[i]->getXY();
		x = coords.first;
		y = coords.second;
		addToRenderBuff(x, y, 'e');
	}
	coords = player->getXY();
	x = coords.first;
	y = coords.second;
	addToRenderBuff(x, y, 'c');
	// 	breakable walls
	// 	unbreakable walls
	// 	walls
	// 	drops
	// 	surface?

}

void		GraphicsHandler::addToRenderBuff(int x, int y, char symbol) {
	typedef void (*addToRenderBuff_t)(int,int,char);
	addToRenderBuff_t	addToRenderBuff = (addToRenderBuff_t) dlsym(_handle, "addToRenderBuff");
	addToRenderBuff(x, y, symbol);
	
}

void		GraphicsHandler::render() {
	typedef void (*render_t)();
	render_t	render = (render_t) dlsym(_handle, "render");
	render();
}

