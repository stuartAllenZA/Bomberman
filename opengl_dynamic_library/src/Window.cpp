//
// Created by Adrian Degenaar on 2017/08/07.
//

//#include <Window.hpp>
#include "../include/Window.hpp"

void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Press any key to exit" << std::endl;
    int temp;
    std::cin >> temp;
    SDL_Quit();
    exit(1);
}

Window::Window() {
    _win = nullptr;
    _GameState = GameState::PLAY;
    init();
    gameLoop();

}

Window::~Window() {
    std::cout << "SDL is closed" << std::endl;
    SDL_Quit();
}

void Window::init() {
    // Init SDL
    SDL_Init(SDL_INIT_EVERYTHING);



    _win = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_OPENGL);
    if (_win == nullptr)
        fatalError("SDL window broke");

    SDL_GLContext contxt = SDL_GL_CreateContext(_win);
    if (contxt == nullptr)
        fatalError("Context went for a ball of shit");

    GLenum error = glewInit();
    if (error != GLEW_OK)
        fatalError("GLEW is screwed");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    glClearColor(0, 0, 1, 1);
}

void Window::input() {
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT :
                _GameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;
        }
    }
}

void Window::gameLoop() {
    while (_GameState != GameState::EXIT) {
        input();
        drawGame();
    }
}

void Window::drawGame() {
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SDL_GL_SwapWindow(_win);
}
