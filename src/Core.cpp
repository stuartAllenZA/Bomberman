#include <Core.hpp>

void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Press any key to exit" << std::endl;
    int temp;
    std::cin >> temp;
    exit(1);
}

Core::Core() {
   // _win = nullptr;
   // _gameState = GameState::PLAY;
//	_game = new Game;
    glfwInit();
    std::cout << "running" << std::endl;
    run();
}

Core::~Core() {
	std::cout << "destructing core" << std::endl;
    //delete _game;
	//_game = nullptr;
}

void	Core::run() {
    std::cout << "initializing" << std::endl;
    init();
    //gameLoop();
	
}

void Core::init() {
    _win = nullptr;
    std::cout << "creating glfw window" << std::endl;
    glfwInit();

    glfwSetTime(0);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    _win = glfwCreateWindow(_width, _height, "Bomberman", nullptr, nullptr);
    if (_win == nullptr)
        fatalError("GLFW context is shot");
    glfwMakeContextCurrent(_win);
    glfwSwapInterval(1);
    std::cout << "glfw window created" << std::endl;
    std::cout << "creating nanogui screen" << std::endl;
    _screen = new nanogui::Screen;
    std::cout << "nanogui screen created" << std::endl;
    std::cout << "initializing nanogui window" << std::endl;
    _screen->initialize(_win, true);
    std::cout << "nanogui window initialized, screen integrated with window" << std::endl;
    std::cout << "visualizing screen" << std::endl;
    _screen->setVisible(true);
    _screen->performLayout();
    std::cout << "starting screen loop" << std::endl;
    nanogui::mainloop(100);
    std::cout << "closing nanogui screen" << std::endl;
    nanogui::shutdown();
    std::cout << "nanogui screen closed successfully" << std::endl;
}

//Core::_key    Core::getAsciiKey(const Uint8*	keyPressArr){
//    if (keyPressArr[SDL_SCANCODE_LEFT])
//        return _key::LEFT;
//    else if (keyPressArr[SDL_SCANCODE_RIGHT])
//        return _key::RIGHT;
//    else if (keyPressArr[SDL_SCANCODE_UP])
//        return _key::UP;
//    else if (keyPressArr[SDL_SCANCODE_DOWN])
//        return _key::DOWN;
//    else if (keyPressArr[SDL_SCANCODE_SPACE])
//        return _key::SPACE;
//    else if (keyPressArr[SDL_SCANCODE_RETURN])
//        return _key::ENTER;
//    else if (keyPressArr[SDL_SCANCODE_ESCAPE])
//        return _key::ESC;
//    else
//        return _key::NONE;
//}

void Core::input() {


    int state = glfwGetKey(_win, GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS)
        _gameState = GameState::EXIT;

//    SDL_Event evnt;
//    const Uint8*	keyPressArr = SDL_GetKeyboardState(NULL); // var to hold the current keypress, SEE https://wiki.libsdl.org/SDL_GetKeyboardState (Liam)
//
//    _key     keyName;
//
//    while (SDL_PollEvent(&evnt)) {
//        switch (evnt.type) {
//            case SDL_QUIT :
//                _gameState = GameState::EXIT;
//                break;
//            case SDL_MOUSEMOTION:
//                std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
//                break;
//        }
//        keyName = getAsciiKey(keyPressArr);
//        switch (keyName) {
//            case _key::LEFT :
//                std::cout << "LEFTKEY!" << std::endl;
//                break;
//            case _key::RIGHT :
//                std::cout << "RIGHTKEY!" << std::endl;
//                break;
//            case _key::UP :
//                std::cout << "UPKEY!" << std::endl;
//                break;
//            case _key::DOWN :
//                std::cout << "DOWNKEY!" << std::endl;
//                break;
//            case _key::SPACE :
//                std::cout << "SPACEKEY!" << std::endl;
//                break;
//            case _key::ENTER :
//                std::cout << "ENTERKEY!" << std::endl;
//                break;
//            case _key::ESC :
//                std::cout << "ESCAPEKEY!" << std::endl;
//                break;
//            case _key::NONE :
//                std::cout << "NONE" << std::endl;
//                break;
//
//        }
//    }
}

void Core::gameLoop() {
    while (_gameState != GameState::EXIT && !glfwWindowShouldClose(_win)) {
        input();
        drawGame();
    }
}

void Core::drawGame() {
    glfwGetFramebufferSize(_win, &_width, &_height);

    glViewport(0, 0, _width, _height);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(_win);
    glfwPollEvents();
}
