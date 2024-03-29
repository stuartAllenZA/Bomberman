#ifndef MENU_HPP
#define MENU_HPP

#pragma once

#ifdef __APPLE__
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#include <GL/glew.h>
#include <nanogui/nanogui.h>
#include <nanogui/screen.h>
#include <nanogui/widget.h>
#include <GLFW/glfw3.h>
#include <utility>
#include <Settings.hpp>
#include <Game.hpp>
#include <Sound.hpp>
#include <sstream>

enum class MenuState {
    PLAYER_SELECT,
    LOAD_SAVE,
    MAIN_MENU,
    SETTINGS,
    KEYBINDING,
    PAUSE,
	DIFFICULTY,
	LEVEL_PASS,
	LEVEL_FAIL,
    NO_MENU
};

enum class BindingButtonState {
	UP_BINDING,
	DOWN_BINDING,
	LEFT_BINDING,
	RIGHT_BINDING,
	ACTION_BINDING,
	ACCEPT_BINDING,
	ESCAPE_BINDING,
	NONE
};

class Menu {
public:
	Menu(int passedWidth, int passedHeight, Game *passedGame, GLFWwindow **passedWin);
	Menu(Menu const &src);
	Menu &operator=(Menu const &src);
	~Menu();
	double          getMouseX() const;
	void            setMouseX(const double newMouseX);
	double          getMouseY() const;
	void            setMouseY(const double newMouseY);
	MenuState       getMenuState() const;
	void            setMenuState(const MenuState newMenuState);
	double			getDelayTimer() const;
	void 			resetDelayTimer();
	void 			incrementDelayTimer();
	double			getMinimumTime() const;
	void			setMinimumTime(const double newMinimumTime);
	Game			*getGame() const;
	void			setGame(Game *newGame);
	GLFWwindow		**getWin() const;
	void			setWin(GLFWwindow **win);
	int				getWidth() const;
	void			setWidth(const int newWidth);
	int				getHeight() const;
	void			setHeight(const int newHeight);

    void			updateKeys();
    void			updateMouse();
	void			menu();
    void            playerSelectMenu();
    void            mainMenu();
    void			settingsMenu();
    void            keyBindingMenu();
    void            pauseMenu();
	void 			difficultyMenu();
	void			levelPassMenu();
	void			levelFailMenu();
	int				checkMenuSelectionKeys();
    bool            checkPlayerNameAvailability(std::string playerNameInputVar);
    void            createButton(std::string playerNameInputVar);
	void			selectButton(std::vector<std::string> playerNames, int nameIndex);
	void			deleteButton(std::vector<std::string> playerNames, int nameIndex);
    void            exitButton();
    void            logoutButton();
    void            newGameButton();
    void            loadGameButton();
    void            playerSelectButton();
    void            settingsButton();
    void            keyBindingButton();
	void 			applyButton(int selectedIndex, Settings *tempSettings);
	int				findKeyForBinding();
	int				checkForKeySymbol(int keyPressed);
	std::string		findNameForBinding(int keyPressed);
	void			bindKeysWithoutConflicts(BindingButtonState bindingButtonState, Settings *tempSettings);
    void            resumeButton();
    void            quitToMenuButton();
    void			renderMenu();
	bool			iequals(const std::string& a, const std::string& b);
	void			errorPopup(const std::string & title, const std::string & message, const std::string & btnText);

private:

	double			_mouseX;
	double			_mouseY;
	MenuState       _menuState;
	double			_delayTimer;
	double 			_minimumTime;
	int				_width;
	int				_height;
	Game            *_game;
	GLFWwindow		**_win;
};

#endif