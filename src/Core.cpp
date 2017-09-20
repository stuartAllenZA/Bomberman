#include <Core.hpp>

Core::Core() {
	//std::cout << "Constructing Core\n";
	this->_width = this->_game.getSettings().getResolutionX();
	this->_height = this->_game.getSettings().getResolutionY();
	this->_menu = new Menu(_width, _height, &_game, &_win);
	std::cout << "Core Constructed\n";
}

Core::Core(Core const & src) {
	//std::cout << "Core Copy-Constructed\n";
	*this = src;
}

Core &			Core::operator=(Core const & src) {
	this->_win = src.getWin();
	this->_game = src.getGame();
	this->_width = src.getWidth();
	this->_height = src.getHeight();
	return (*this);
}

Core::~Core() {
	//std::cout << "De-Constructing Core\n";
	//std::cout << "Closing Nanogui Screen" << std::endl;
	nanogui::shutdown();
	//std::cout << "Nanogui screen closed successfully" << std::endl;
	delete this->_menu;
	this->_menu = nullptr;
	glfwTerminate();
	std::cout << "Core De-Constructed\n";
}

void			Core::run() {
	//std::cout << "Starting Core" << std::endl;
	init();
	gameLoop();
	std::cout << "Done with gameLoop!" << std::endl;
}

void			Core::init() {
	std::cout << "Initializing Core" << std::endl;
	this->_game.initSound();
	_win = nullptr;
	//std::cout << "Creating GLFW Window" << std::endl;
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
	else {
		int xPos, yPos;
		glfwGetWindowPos(_win, &xPos, &yPos);
		this->_game.setWindowPos(xPos, yPos);
	}
	glfwMakeContextCurrent(_win);
	glfwSwapInterval(1);

	std::cout << "GLFW Window Created." << std::endl;
}

void			Core::gameLoop() {
	GameState gs;
	bool loop = true;

	//std::cout << "THE ORIGINAL SETTINGS!!!" << std::endl << this->_game.getSettings() << std::endl;
	glfwSetWindowPos(_win, this->_game.getSettings().getXPos(), this->_game.getSettings().getYPos());
	while (loop == true && !glfwWindowShouldClose(_win)) {
		input();
		gs = this->_game.getGameState();
		switch (gs) {
			case GameState::MENU :
			_game.startMenuMusic();
			_menu->menu();
			_game.stopMenuMusic();
			break;
			case GameState::PLAY :
			_game.startGameMusic();
			initPlay();
			_game.stopGameMusic();
			break;
			case GameState::EXIT :
			loop = false;
			break;
		}
		drawGame();
		std::cout << "Main gameLoop looping." << std::endl;
	}
}

void			Core::input() {
	_menu->updateKeys();
	_menu->updateMouse();
}

void			Core::drawGame() {
	glfwGetFramebufferSize(_win, &_width, &_height);

	glViewport(0, 0, _width, _height);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(_win);
	glfwPollEvents();
}

void			Core::fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Press any key to exit" << std::endl;
	int temp;
	std::cin >> temp;
	std::exit(1);
}

void			Core::initPlay() {
	//std::cout << "playing, ESC to exit" << std::endl;
	std::cout << "Playing, on 10x10 board" << std::endl;
	_game.initLevelOne();
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
	while (_game.getGameState() == GameState::PLAY) {
		glfwPollEvents();
		updateKeys();
		if (_game.getKeyPressArr(ESCAPE)){
			this->_game.setGameState(GameState::MENU);
			_menu->setMenuState(MenuState::PAUSE);
		}
	}
}

void			Core::updateKeys() {
	if (glfwGetKey(_win, this->_game.getSettings().getUpKey()) == GLFW_PRESS)
		this->_game.setKeyPressArr(UP, true);
	else
		this->_game.setKeyPressArr(UP, false);

	if (glfwGetKey(_win, this->_game.getSettings().getDownKey()) == GLFW_PRESS)
		this->_game.setKeyPressArr(DOWN, true);
	else
		this->_game.setKeyPressArr(DOWN, false);

	if (glfwGetKey(_win, this->_game.getSettings().getLeftKey()) == GLFW_PRESS)
		this->_game.setKeyPressArr(LEFT, true);
	else
		this->_game.setKeyPressArr(LEFT, false);

	if (glfwGetKey(_win, this->_game.getSettings().getRightKey()) == GLFW_PRESS)
		this->_game.setKeyPressArr(RIGHT, true);
	else
		this->_game.setKeyPressArr(RIGHT, false);

	if (glfwGetKey(_win, this->_game.getSettings().getActionKey()) == GLFW_PRESS)
		this->_game.setKeyPressArr(ACTION, true);
	else
		this->_game.setKeyPressArr(ACTION, false);

	if (glfwGetKey(_win, this->_game.getSettings().getAcceptKey()) == GLFW_PRESS)
		this->_game.setKeyPressArr(ACCEPT, true);
	else
		this->_game.setKeyPressArr(ACCEPT, false);

	if (glfwGetKey(_win, this->_game.getSettings().getEscapeKey()) == GLFW_PRESS)
		this->_game.setKeyPressArr(ESCAPE, true);
	else
		this->_game.setKeyPressArr(ESCAPE, false);
}

Game			Core::getGame() const {
	return (this->_game);
}

void			Core::setGame(const Game newGame) {
	this->_game = newGame;
}

GLFWwindow		*Core::getWin() const {
	return (this->_win);
}

void			Core::setWin(GLFWwindow *win) {
	this->_win = win;
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