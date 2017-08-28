#ifndef CORE_CLASS_HPP_
#define CORE_CLASS_HPP_

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
private:
    GLFWwindow *_win;
    nanogui::Screen *_screen;
    int _width = 800;
    int _height = 600;
    GameState _gameState;
    enum class _key {LEFT, RIGHT, UP, DOWN, SPACE, ENTER, ESC, NONE};
	Game	*_game;

public:
    Core();
    ~Core();

	void run();
    void init();
    void input();
    void gameLoop();
    void drawGame();
    //_key getAsciiKey(const Uint8*	keyPressArr);
};


#endif
