#ifndef CORE_HPP
#define CORE_HPP

#pragma once

#include <GL/glew.h>
#include <nanogui/nanogui.h>
#include <nanogui/screen.h>
#include <nanogui/widget.h>
#include <GLFW/glfw3.h>
#include "Character.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "Menu.hpp"

class Core {
public:
	Core();
	Core(Core const &src);
	Core &operator=(Core const &src);
	~Core();
	Game			getGame() const;
	void			setGame(const Game newGame);
	GLFWwindow		*getWin() const;
	void			setWin(GLFWwindow *win);
	int				getWidth() const;
	void			setWidth(const int newWidth);
	int				getHeight() const;
	void			setHeight(const int newHeight);


	void			init();
	void			input();
	void			run();
	void			gameLoop();
	void			drawGame();
	void			newPlayer(const std::string playerName);
	void			initPlay();
	void			load();
	void			settings();
	void			save();
	void			exit();
	void			setExit();
	void			fatalError(std::string errorString);

private:

	int				_width;
	int				_height;
	Game			_game;
    Menu            *_menu;
    GLFWwindow		*_win;
};

#endif