#ifndef CORE_HPP
#define CORE_HPP

#pragma once

#include <iostream>
#include "../../.brew/Cellar/glew/2.1.0/include/GL/glew.h"
#include "../../.brew/include/nanogui/nanogui.h"
#include "../../.brew/Cellar/glfw/3.2.1/include/GLFW/glfw3.h"
#include "Character.hpp"
#include "Exceptions.hpp"
#include "Game.hpp"
#include "GraphicsHandler.hpp"
#include "Player.hpp"
#include "Settings.hpp"

class Core {
public:
    Core();

    Core(Core const &src);

    Core &operator=(Core const &src);

    ~Core();

    void run();

    void init();

    void input();

    void gameLoop();

    void drawGame();

    //__________________________GETTERS AND SETTERS________________________________________

    Game *getGame() const;

    void setGame(Game *newGame);

    GLFWwindow *getWin() const;

    void setWin(GLFWwindow *win);

    nanogui::Screen *getScreen() const;

    void setScreen(nanogui::Screen *screen);

    int getWidth() const;

    void setWidth(const int newWidth);

    int getHeight() const;

    void setHeight(const int newHeight);

    //__________________________________END______________________________________

private:

    GLFWwindow *_win;
    nanogui::Screen *_screen;
    int _width = 800;
    int _height = 600;
    GameState _gameState;
    enum class _key {
        LEFT, RIGHT, UP, DOWN, SPACE, ENTER, ESC, NONE};
    Game *_game;
};


#endif
