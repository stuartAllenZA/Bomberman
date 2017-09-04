#include <Core.hpp>

Core::Core() {
	std::cout << "Constructing Core\n";
	this->_game = new Game;
	Settings settings = this->_game->getSettings();
	this->_width = settings.getResolutionX();
	this->_height = settings.getResolutionY();
	glfwInit();
	std::cout << "Core Constructed\n";
}

Core::Core(Core const & src) {
	std::cout << "Core Copy-Constructed\n";
	*this = src;
}

Core &			Core::operator=(Core const & src) {
	this->_win = src.getWin();
	this->_screen = src.getScreen();
	this->_game = src.getGame();
	this->_width = src.getWidth();
	this->_height = src.getHeight();
	return (*this);
}

Core::~Core() {
	std::cout << "De-Constructing Core\n";
	delete this->_game;
	this->_game = nullptr;
	std::cout << "closing nanogui screen" << std::endl;
	nanogui::shutdown();
	std::cout << "nanogui screen closed successfully" << std::endl;
	std::cout << "Core De-Constructed\n";
}

void			Core::run() {
	std::cout << "initializing" << std::endl;
	init();
	// Start main menu (set game state, render menu)
	// Simulate selection of 'New Game'
	// Spawn player
	// Spawn u-box
	// Spawn box0 - empty
	// Spawn box1 - enemy
	// Spawn box2 - upgrade
	// Spawn box3 - hatch
	// Move player
	// Place bomb
	// move player
	// detonate bomb
	// destroy box
	// Move player
	// Place bomb
	// move player
	// explode bomb
	// destroy box
	// drop enemy
	// move player
	// move enemy
	// place bomb
	// move player
	// move enemy
	// detonate bomb
	// kill enemy
	// xp up player
	// move player
	// place bomb
	// move player
	// detonate bomb
	// destroy box
	// drop upgrade
	// move player
	// collect upgrade
	// activate upgrade on player
	// move player
	// place bomb
	// move player
	// detonate bomb
	// destroy box
	// drop hatch
	// move player
	// finish demo
}

void			Core::init() {
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

void			Core::input() {
	int state = glfwGetKey(_win, GLFW_KEY_ESCAPE);

	if (state == GLFW_PRESS)
		this->_game->setState(GameState::EXIT);
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

void			Core::gameLoop() {
	while (this->_game->getState() != GameState::EXIT && !glfwWindowShouldClose(_win)) {
		input();
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
		drawGame();
	}
}

void			Core::drawGame() {
	glfwGetFramebufferSize(_win, &_width, &_height);

	glViewport(0, 0, _width, _height);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(_win);
	glfwPollEvents();
}

Game			*Core::getGame() const {
	return (this->_game);
}

void			Core::setGame(Game *newGame) {
	this->_game = newGame;
}

GLFWwindow		*Core::getWin() const {
	return (this->_win);
}

void			Core::setWin(GLFWwindow *win) {
	this->_win = win;
}

nanogui::Screen	*Core::getScreen() const {
	return (this->_screen);
}

void			Core::setScreen(nanogui::Screen *screen){
	this->_screen = screen;
}

int				Core::getWidth() const {
	return (this->_width);
}

void			Core::setWidth(const int newWidth) {
	this->_width = newWidth;
}

int				Core::getHeight() const {
	return (this->_height);
}

void			Core::setHeight(const int newHeight) {
	this->_height = newHeight;
}

void			Core::fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Press any key to exit" << std::endl;
	int temp;
	std::cin >> temp;
	exit(1);
}