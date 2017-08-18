#include <Core.hpp>

void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Press any key to exit" << std::endl;
    int temp;
    std::cin >> temp;
    SDL_Quit();
    exit(1);
}

Core::Core() {
    _win = nullptr;
    _gameState = GameState::PLAY;
	_game = new Game;
}

Core::~Core() {
	delete _game;
	_game = nullptr;
    std::cout << "SDL is closed" << std::endl;
    SDL_Quit();
}

void	Core::run() {
    init();
    gameLoop();
	
}

void Core::init() {
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

    glClearColor(0, 0, 0, 0);
}

Core::_key    Core::getAsciiKey(const Uint8*	keyPressArr){
    if (keyPressArr[SDL_SCANCODE_LEFT])
        return _key::LEFT;
    else if (keyPressArr[SDL_SCANCODE_RIGHT])
        return _key::RIGHT;
    else if (keyPressArr[SDL_SCANCODE_UP])
        return _key::UP;
    else if (keyPressArr[SDL_SCANCODE_DOWN])
        return _key::DOWN;
    else if (keyPressArr[SDL_SCANCODE_SPACE])
        return _key::SPACE;
    else if (keyPressArr[SDL_SCANCODE_RETURN])
        return _key::ENTER;
    else if (keyPressArr[SDL_SCANCODE_ESCAPE])
        return _key::ESC;
    else
        return _key::NONE;
}

void Core::input() {
    SDL_Event evnt;
    const Uint8*	keyPressArr = SDL_GetKeyboardState(NULL); // var to hold the current keypress, SEE https://wiki.libsdl.org/SDL_GetKeyboardState (Liam)

    _key     keyName;

    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT :
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;
        }
        keyName = getAsciiKey(keyPressArr);
        switch (keyName) {
            case _key::LEFT :
                std::cout << "LEFTKEY!" << std::endl;
                break;
            case _key::RIGHT :
                std::cout << "RIGHTKEY!" << std::endl;
                break;
            case _key::UP :
                std::cout << "UPKEY!" << std::endl;
                break;
            case _key::DOWN :
                std::cout << "DOWNKEY!" << std::endl;
                break;
            case _key::SPACE :
                std::cout << "SPACEKEY!" << std::endl;
                break;
            case _key::ENTER :
                std::cout << "ENTERKEY!" << std::endl;
                break;
            case _key::ESC :
                std::cout << "ESCAPEKEY!" << std::endl;
                break;
            case _key::NONE :
                std::cout << "NONE" << std::endl;
                break;

        }
    }
}

void Core::gameLoop() {
    while (_gameState != GameState::EXIT) {
        input();
        drawGame();
    }
}

void Core::drawGame() {
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SDL_GL_SwapWindow(_win);
}
