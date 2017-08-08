//
// Created by Adrian Degenaar on 2017/08/07.
//

#ifndef BOMBERMAN_WINDOW_HPP
#define BOMBERMAN_WINDOW_HPP

#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "../../../.brew/Cellar/glew/2.1.0/include/GL/glew.h"

enum class GameState {PLAY, EXIT};

class Window {
private:
    SDL_Window *_win;
    int _width = 800;
    int _height = 600;
    GameState _GameState;

public:
    Window();
    ~Window();

    void init();

    void input();
    void gameLoop();
    void drawGame();
};


#endif //BOMBERMAN_WINDOW_HPP
