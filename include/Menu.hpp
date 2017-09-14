#ifndef MENU_HPP
#define MENU_HPP

#pragma once

#include <GL/glew.h>
#include <nanogui/nanogui.h>
#include <nanogui/screen.h>
#include <nanogui/widget.h>
#include <GLFW/glfw3.h>
#include "Settings.hpp"
#include "Game.hpp"
#include "Sound.hpp"

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

enum class ResolutionState {
    SVGA,       //800x600   4:3
    XGA,        //1024x768  4:3
    WXGA        //1280x800  16:10
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
    bool			getKeyPressArr(const int index) const;
    void			setKeyPressArr(const int index, const bool newChoice);
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
    Settings        *getSettings() const;
    void            setSettings(Settings *newSettings);

    void			updateKeys();
    void			updateMouse();
    void			menu();
    void            playerSelectMenu();
    void            mainMenu();
    void			settingsMenu();
    void            pauseMenu();
    bool            checkPlayerNameAvailability(std::string playerNameInputVar);
    void            createButton(std::string playerNameInputVar);
    void            exitButton();
    void            newGameButton();
    void            loadGameButton();
    void            playerSelectButton();
    void            settingsButton();
    void            resumeButton();
    void            quitToMenuButton();
    void            resetToDefaultButton();
    void			renderMenu();

private:

    double			_mouseX;
    double			_mouseY;
    bool			_keyPressArr[7];
    MenuState       _menuState;
    double			_delayTimer;
    double 			_minimumTime;
    int				_width;
    int				_height;
    Game            *_game;
    GLFWwindow		**_win;
    Settings        *_settings;
};

#endif