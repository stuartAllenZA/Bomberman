#include <Core.hpp>

nanogui::Screen *screen = nullptr;

Core::Core() {
	std::cout << "Constructing Core\n";
	this->_game = new Game;
	this->_width = this->_game->getSettings().getResolutionX();
	this->_height = this->_game->getSettings().getResolutionY();
    this->_menuState = MenuState::PLAYER_SELECT;
	std::cout << "Core Constructed\n";
}

Core::Core(Core const & src) {
	std::cout << "Core Copy-Constructed\n";
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

	std::cout << "De-Constructing Core\n";
	delete this->_game;
	this->_game = nullptr;
	std::cout << "closing nanogui screen" << std::endl;
	nanogui::shutdown();
	std::cout << "nanogui screen closed successfully" << std::endl;
	glfwTerminate();
	std::cout << "Core De-Constructed\n";
}

void			Core::run() {
	std::cout << "initializing" << std::endl;
	init();
	gameLoop();
	std::cout << "Done" << std::endl;
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
	glfwSetCursorPosCallback(_win,
            [](GLFWwindow *, double x, double y) {
            screen->cursorPosCallbackEvent(x, y);
        }
    );

    glfwSetMouseButtonCallback(_win,
        [](GLFWwindow *, int button, int action, int modifiers) {
            screen->mouseButtonCallbackEvent(button, action, modifiers);
        }
    );
	std::cout << "glfw window created" << std::endl;
}

void			Core::gameLoop() {
	GameState gs;
	bool loop = true;

	while (loop == true && !glfwWindowShouldClose(_win)) {
		input();
		gs = this->_game->getGameState();
		switch (gs) {
			case GameState::MENU :
			menu();
			break;
			case GameState::PLAY :
			initPlay();
			break;
			case GameState::LOAD :
			load();
			break;
			case GameState::SET :
			settings();
			break;
			case GameState::SAVE :
			save();
			break;
			case GameState::EXIT :
			loop = false;
			break;
		}
		drawGame();
		std::cout << "looping" << std::endl;
	}
}

void			Core::input() {
	updateMouse();
	updateKeys();
}

void			Core::drawGame() {
	glfwGetFramebufferSize(_win, &_width, &_height);

	glViewport(0, 0, _width, _height);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(_win);
	glfwPollEvents();
}

void	        Core::menu() {
#if defined(NANOGUI_GLAD)
	std::cout << "initializing GLAD loader" << std::endl;
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
			throw std::runtime_error("Could not initialize GLAD!");
		glGetError(); // pull and ignore unhandled errors like GL_INVALID_ENUM
#endif
	std::cout << "creating nanogui screen" << std::endl;
	screen = new nanogui::Screen;
	std::cout << "nanogui screen created" << std::endl;
	std::cout << "initializing nanogui window" << std::endl;
	screen->initialize(_win, true);
	std::cout << "nanogui window initialized, screen integrated with window" << std::endl;
    while (this->_game->getGameState() == GameState::MENU) {
        switch (_menuState) {
            case MenuState::PLAYER_SELECT :
                playerSelectMenu();
                break;
            case MenuState::MAIN_MENU :
                mainMenu();
                break;
            case MenuState::LOAD_SAVE :
                load();
                break;
            case MenuState::SETTINGS :
                settingsMenu();
                break;
			case MenuState::PAUSE :
				pauseMenu();
				break;
            case MenuState::NO_MENU :
                break;
        }
    }
}

void            Core::playerSelectMenu() {
    nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
    nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), "Select a player");
    std::string     playerNameInput = "PRESS ENTER TO START";
    gui->addVariable("Create a new player", playerNameInput);
    screen->setVisible(true);
    screen->performLayout();
    nanoguiWindow->center();
	resetDelayTimer();
    while (!glfwWindowShouldClose(_win) && _menuState == MenuState::PLAYER_SELECT){
        glfwPollEvents();
        updateKeys();
        updateMouse();
        if (_keyPressArr[ENTER])
            _menuState = MenuState::MAIN_MENU;
		if (_keyPressArr[ESC] && getDelayTimer() >= 100) {
			this->_game->setGameState(GameState::EXIT);
			_menuState = MenuState::NO_MENU;
		}
		std::cout << getDelayTimer() << std::endl;
        renderMenu();
    }
	if (glfwWindowShouldClose(_win))
		this->_game->setGameState(GameState::EXIT);
    nanoguiWindow->dispose();
}

void            Core::mainMenu() {
    nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
    nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(100, 100), "Bomberman");

    gui->addButton("New Game", [this]() {
        std::cout << "New Game pressed." << std::endl;
        this->_game->setGameState(GameState::PLAY);
		this->_game->setPlayState(PlayState::GAME_PLAY);
        _menuState = MenuState::NO_MENU;
    });


    if (this->_game->getHasSave())
        gui->addButton("Load Game", []() { std::cout << "HAS SAVES" << std::endl; });
    else
		gui->addButton("Load Game", []() { std::cout << "NO SAVES" << std::endl; });

	gui->addButton("Settings", [this]() {
        std::cout << "Settings pressed." << std::endl;
		_menuState = MenuState::SETTINGS;
    })->setBackgroundColor(Eigen::Vector4i(255, 255, 255, 255));

    gui->addButton("Exit", [this] {
        this->_game->setGameState(GameState::EXIT);
        _menuState = MenuState::NO_MENU;
    });

    std::cout << "visualizing screen" << std::endl;
    screen->setVisible(true);
    screen->performLayout();
    nanoguiWindow->center();

    std::cout << "starting screen loop" << std::endl;
	resetDelayTimer();
    while (!glfwWindowShouldClose(_win) && _menuState == MenuState::MAIN_MENU){
        glfwPollEvents();
        updateKeys();
        updateMouse();
		if (_keyPressArr[ESC] && getDelayTimer() >= 100) {
			std::cout << "escape pressed, player select menu" << std::endl;
			_menuState = MenuState::PLAYER_SELECT;
		}
		else if (_keyPressArr[ENTER] && getDelayTimer() >= 100) {
			std::cout << "pressed enter, starting new game" << std::endl;
            this->_game->setGameState(GameState::PLAY);
			_menuState = MenuState::NO_MENU;
        }
	renderMenu();
    }
	if (glfwWindowShouldClose(_win))
		this->_game->setGameState(GameState::EXIT);
	nanoguiWindow->dispose();
}

void			Core::settingsMenu(){
	nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), "SETTINGS");

	nanogui::Widget *tools = new nanogui::Widget(screen);

//	std::cout << "settings menu" << std::endl;
//	tools->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Horizontal, nanogui::Alignment::Middle, 0, 6));
//	std::cout << "settings menu" << std::endl;
//	nanogui::Button *b = new nanogui::Button(nanoguiWindow, "Plain button");
//	std::cout << "settings menu" << std::endl;
//	b = new nanogui::Button(tools, "ACCEPT");
//	b->setCallback([&]{
//		_menuState = MenuState::MAIN_MENU;
//	});
//	b = new nanogui::Button(tools, "APPLY");
//	b->setCallback([&]{
//		_menuState = MenuState::PLAYER_SELECT;
//	});
	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();
	resetDelayTimer();
	while (!glfwWindowShouldClose(_win) && _menuState == MenuState::SETTINGS){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (_keyPressArr[ESC] && getDelayTimer() >= 100)
		{
			if (this->_game->getPlayState() == PlayState::GAME_PLAY)
				_menuState = MenuState::PAUSE;
			else
				_menuState = MenuState::MAIN_MENU;
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(_win))
		this->_game->setGameState(GameState::EXIT);
	nanoguiWindow->dispose();
}

void            Core::pauseMenu() {
    nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
    nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), "PAUSED");

    gui->addButton("Resume", [this] {
        this->_game->setGameState(GameState::PLAY);
        _menuState = MenuState::NO_MENU;
    });

	gui->addButton("Settings", [this] {
		_menuState = MenuState::SETTINGS;
	});

    gui->addButton("Quit to Menu", [this] {
        _menuState = MenuState::MAIN_MENU;
		this->_game->setPlayState(PlayState::PLAYER_SELECT);
    });

    gui->addButton("Exit Program", [this] {
        this->_game->setGameState(GameState::EXIT);
        _menuState = MenuState::NO_MENU;
		this->_game->setPlayState(PlayState::PLAYER_SELECT);
    });

	screen->setVisible(true);
    screen->performLayout();
    nanoguiWindow->center();
	resetDelayTimer();
    while (!glfwWindowShouldClose(_win) && _menuState == MenuState::PAUSE){
        glfwPollEvents();
        updateKeys();
        updateMouse();
		if (_keyPressArr[ENTER] && getDelayTimer() >= 100)
		{
			_menuState = MenuState::NO_MENU;
			this->_game->setGameState(GameState::PLAY);
		}
		renderMenu();
    }
	if (glfwWindowShouldClose(_win))
		this->_game->setGameState(GameState::EXIT);
    nanoguiWindow->dispose();
}

void			Core::updateKeys() {
	int     state;
	bool    pressed = false;

	state = glfwGetKey(_win, GLFW_KEY_LEFT);
	if (state == GLFW_PRESS)
		_keyPressArr[LEFT] = true;
	else
		_keyPressArr[LEFT] = false;
	state = glfwGetKey(_win, GLFW_KEY_RIGHT);
	if (state == GLFW_PRESS)
		_keyPressArr[RIGHT] = true;
	else
		_keyPressArr[RIGHT] = false;
	state = glfwGetKey(_win, GLFW_KEY_UP);
	if (state == GLFW_PRESS)
		_keyPressArr[UP] = true;
	else
		_keyPressArr[UP] = false;
	state = glfwGetKey(_win, GLFW_KEY_DOWN);
	if (state == GLFW_PRESS)
		_keyPressArr[DOWN] = true;
	else
		_keyPressArr[DOWN] = false;
	state = glfwGetKey(_win, GLFW_KEY_SPACE);
	if (state == GLFW_PRESS)
		_keyPressArr[SPACE] = true;
	else
		_keyPressArr[SPACE] = false;
	state = glfwGetKey(_win, GLFW_KEY_ENTER);
	if (state == GLFW_PRESS)
		_keyPressArr[ENTER] = true;
	else
		_keyPressArr[ENTER] = false;
	state = glfwGetKey(_win, GLFW_KEY_ESCAPE);
	if (state == GLFW_PRESS)
		_keyPressArr[ESC] = true;
	else
		_keyPressArr[ESC] = false;
}

void			Core::updateMouse() {
	int				state;
	static bool		wasClicked = false;
	static double	clickX;
	static double	clickY;

	glfwGetCursorPos(_win, &_mouseX, &_mouseY);
	state = glfwGetMouseButton(_win, GLFW_MOUSE_BUTTON_1);
	if (state == GLFW_PRESS && wasClicked == false) {
		std::cout << "clicked at:   " << _mouseX << ",  " << _mouseY << std::endl;
		wasClicked = true;
		clickX = _mouseX;
		clickY = _mouseY;
	}
	else if (state == GLFW_RELEASE && wasClicked) {
		std::cout << "released at:  " << _mouseX << ",  " << _mouseY << std::endl;
		wasClicked = false;
	}
}

void			Core::fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Press any key to exit" << std::endl;
	int temp;
	std::cin >> temp;
	std::exit(1);
}

void			Core::initPlay() {
	std::cout << "playing, ESC to exit" << std::endl;
//	if (this->_game->getSettings().getLastPlayer().empty())
//        newPlayer(); //function that uses nanogui to get the name of player and create player
//    else
//        this->_game->loadPlayer(this->_game->getSettings().getLastPlayer());
    if (_keyPressArr[ESC]){
        this->_game->setGameState(GameState::MENU);
        _menuState = MenuState::PAUSE;
    }
}

void			Core::newPlayer() {
	//TODO: ADD NEW WINDOW TO MAKE PLAYERS
	this->_game->setPlayer(new Player("Bob"));
}

void			Core::load() {

}

void			Core::settings() {

}

void			Core::save() {

}

void			Core::renderMenu() {
	glfwGetFramebufferSize(_win, &_width, &_height);
	glViewport(0, 0, _width, _height);
	glClear(GL_COLOR_BUFFER_BIT);

	screen->drawContents();
	screen->drawWidgets();
	glfwSwapBuffers(_win);
	incrementDelayTimer();
	incrementDelayTimer();
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

bool			*Core::getKeyPressArr(){
	return (this->_keyPressArr);
}

void			Core::setKeyPressArr(const bool newUp, const bool newDown, const bool newLeft, const bool newRight, const bool newSpace, const bool newEnter, const bool newEsc){
	this->_keyPressArr[UP] = newUp;
	this->_keyPressArr[DOWN] = newDown;
	this->_keyPressArr[LEFT] = newLeft;
	this->_keyPressArr[RIGHT] = newRight;
	this->_keyPressArr[SPACE] = newSpace;
	this->_keyPressArr[ENTER] = newEnter;
	this->_keyPressArr[ESC] = newEsc;
}

MenuState       Core::getMenuState() const {
    return (this->_menuState);
}

void            Core::setMenuState(const MenuState newMenuState){
    this->_menuState = newMenuState;
}

double			Core::getDelayTimer() const {
	return (this->_delayTimer);
}

void 			Core::resetDelayTimer() {
	this->_delayTimer = 0;
}

void			Core::incrementDelayTimer() {
	this->_delayTimer++;
}