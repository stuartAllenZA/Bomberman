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
	glfwInit();
	glfwSetTime(0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);
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
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
	}
	_gfx = new GraphicsEngine(&_game, &_win);
	_gfx->init();
	//_gfx->renderText();
	std::cout << "GLFW Window Created." << std::endl;
}

void			Core::gameLoop() {
	GameState gs;
	bool loop = true;

	//std::cout << "THE ORIGINAL SETTINGS!!!" << std::endl << this->_game.getSettings() << std::endl;
	glfwSetWindowPos(_win, this->_game.getSettings().getXPos(), this->_game.getSettings().getYPos());
	while (loop == true && !glfwWindowShouldClose(_win)) {
		input();
	//	std::cout << "post input\n";
		gs = this->_game.getGameState();
		switch (gs) {
			case GameState::MENU :
//				if (_menu->getMenuState() == MenuState::PLAYER_SELECT)
//					_game.startMenuMusic();
//				else if (_menu->getMenuState() == MenuState::PAUSE)
//					_game.resumeMenuMusic();
				_menu->menu();
				_game.pauseMenuMusic();
				break;
			case GameState::PLAY :
				if (_game.getPlayState() == PlayState::GAME_INIT) {
					_gfx->initCamera();
					_game.startGameMusic();
				}
				else if (_game.getPlayState() == PlayState::GAME_PLAY)
					_game.resumeGameMusic();
				play();
				_game.pauseGameMusic();
				break;
			case GameState::EXIT :
				loop = false;
				break;
		}
	//	std::cout << "Main gameLoop looping." << std::endl;
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

void			Core::play() {
	//std::cout << "Playing, ESC to exit" << std::endl;
	if (_game.getPlayState() == PlayState::GAME_INIT) {
		_game.reset();
		//_game.initLevelOne();
		_game.initTestMap();
	}
	else if (_game.getPlayState() == PlayState::GAME_LOAD) {
		_game.reset();
		if (_game.getPlayer().getLevel() == 0)
			_game.initLevelOne();
		else if (_game.getPlayer().getLevel() == 1)
			_game.initLevelTwo();
		else if (_game.getPlayer().getLevel() == 2)
			_game.initLevelThree();
	}
	_game.initMapState();
	_game.setPlayState(PlayState::GAME_PLAY);
	//std::cout << _game << std::endl;
	glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	std::cout << "this is the gamestate ";
	if (_game.getGameState() == GameState::PLAY)
		std::cout << "PLAY" << std::endl;
	if (_game.getGameState() == GameState::MENU)
		std::cout << "MENU" << std::endl;
	if (_game.getGameState() == GameState::EXIT)
		std::cout << "MENU" << std::endl;
	while (!glfwWindowShouldClose(_win) && _game.getGameState() == GameState::PLAY) {
		//std::cout << "check for keys loop" << std::endl;
		glfwPollEvents();
		updateKeys();
		_game.controller();
		_gfx->render();	
		if (_game.getKeyPressArr(ESCAPE)){
			this->_game.setGameState(GameState::MENU);
			_menu->setMenuState(MenuState::PAUSE);
		}
	}
	if (glfwGetKey(_win, GLFW_KEY_P) == GLFW_PRESS) {
		std::cout << "P PRESSED" << std::endl;
		_menu->setMenuState(MenuState::LEVEL_PASS);
		_game.setGameState(GameState::MENU);
	}
	if (glfwGetKey(_win, GLFW_KEY_F) == GLFW_PRESS) {
		_menu->setMenuState(MenuState::LEVEL_FAIL);
		_game.setGameState(GameState::MENU);
	}
	glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	this->_game.setGameState(GameState::MENU);
	_menu->setMenuState(MenuState::PAUSE);
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
