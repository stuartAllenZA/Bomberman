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

#define UP		0
#define DOWN	1
#define LEFT	2
#define RIGHT	3
#define SPACE	4
#define ENTER	5
#define ESC		6

enum class MenuState {
    PLAYER_SELECT,
    LOAD_SAVE,
    MAIN_MENU,
    SETTINGS,
    PAUSE,
    NO_MENU
};

class Core {
public:
	Core();
	Core(Core const &src);
	Core &operator=(Core const &src);
	~Core();
	Game			*getGame() const;
	void			setGame(Game *newGame);
	GLFWwindow		*getWin() const;
	void			setWin(GLFWwindow *win);
	int				getWidth() const;
	void			setWidth(const int newWidth);
	int				getHeight() const;
	void			setHeight(const int newHeight);
	bool			*getKeyPressArr();
	void			setKeyPressArr(const bool newUp, const bool newDown, const bool newlLeft, const bool newRight, const bool newSpace, const bool newEnter, const bool newEsc);
    MenuState       getMenuState();
    void            setMenuState(const MenuState newMenuState);

	void			init();
	void			input();
	void			updateKeys();
	void			updateMouse();
	void			run();
	void			gameLoop();
	void			menu();
	void            playerSelectMenu();
    void            mainMenu();
	void			settingsMenu();
	void            pauseMenu();
	void			drawGame();
	void			newPlayer();
	void			initPlay();
	void			load();
	void			settings();
	void			save();
	void			exit();
	void			setExit();
	void			fatalError(std::string errorString);
    void            newGameButton();
    void            loadGameButton();
    void            settingsButton();

private:

	GLFWwindow		*_win;
	int				_width;
	int				_height;
	Game			*_game;
	double			_mouseX;
	double			_mouseY;
	bool			_keyPressArr[7];
    MenuState       _menuState;
};

#endif