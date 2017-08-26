#ifndef CORE_HPP
#define CORE_HPP

#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "../../.brew/Cellar/glew/2.1.0/include/GL/glew.h"
#include "Character.hpp"
#include "Exceptions.hpp"
#include "Game.hpp"
#include "GraphicsHandler.hpp"
#include "Player.hpp"
#include "Settings.hpp"

enum class		keys {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	SPACE,
	ENTER,
	ESC,
	NONE
};

class Core {
public:
	Core();
	Core(Core const & src);
	~Core();
	Core & 		operator=(Core const & src);
	SDL_Window	*getWin() const;
	void		setWin(SDL_Window	*newWin);
	Game		*getGame() const;
	void		setGame(Game *newGame);
	int			getWidth() const;
	void		setWidth(const int newWidth);
	int			getHeight() const;
	void		setHeight(const int newHeight);

	void		run();
	void		init();
	void		input();
	void		gameLoop();
	void		drawGame();
	keys		getAsciiKey(const Uint8*	keyPressArr);
	void		fatalError(std::string errorString);

private:
	SDL_Window	*_win;
	Game		*_game;
	int			_width;
	int			_height;
};


#endif
