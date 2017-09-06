#ifndef CORE_HPP
#define CORE_HPP

#pragma once

#include <iostream>
#include <GL/glew.h>
#include <nanogui/nanogui.h>
#include <nanogui/screen.h>
#include <nanogui/widget.h>
#include <GLFW/glfw3.h>
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
    Core(Core const &src);
    Core &operator=(Core const &src);
    ~Core();
    void                updateKeys();
    void                updateMouse();
    void                run();
    void                init();
    void                input();
    void                gameLoop();
    void                mainMenu();
    void                drawGame();
	void				newPlayer();
    void	    		initPlay();
    void		    	load();
    void			    settings();
    void			    save();
    void			    exit();
    void		        fatalError(std::string errorString);

    //__________________________GETTERS AND SETTERS________________________________________

    Game                *getGame() const;
    void                setGame(Game *newGame);
    GLFWwindow          *getWin() const;
    void                setWin(GLFWwindow *win);
    nanogui::Screen     *getScreen() const;
    void                setScreen(nanogui::Screen *screen);
    int                 getWidth() const;
    void                setWidth(const int newWidth);
    int                 getHeight() const;
    void                setHeight(const int newHeight);
    keys                getKeyPressed() const;
    void                setKeyPressed(const keys newkey);
    keys                getPreKeyPressed() const;
    void                setPreKeyPressed(const keys newkey);

    //__________________________________END______________________________________

private:

    GLFWwindow          *_win;
    nanogui::Screen     *_screen;
    int                 _width;
    int                 _height;
    Game                *_game;
    keys                _keyPressed;
    double              _mouseX;
    double              _mouseY;
    keys                _preKeyPressed;
};

#endif
