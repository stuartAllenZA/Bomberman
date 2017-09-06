#include <Core.hpp>

Core::Core() {
	std::cout << "Constructing Core\n";
	this->_game = new Game;
	this->_width = this->_game->getSettings().getResolutionX();
	this->_height = this->_game->getSettings().getResolutionY();
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
			mainMenu();
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

void	Core::mainMenu() {
#if defined(NANOGUI_GLAD)
	std::cout << "initializing GLAD loader" << std::endl;
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
			throw std::runtime_error("Could not initialize GLAD!");
		glGetError(); // pull and ignore unhandled errors like GL_INVALID_ENUM
#endif
	std::cout << "creating nanogui screen" << std::endl;
	_screen = new nanogui::Screen;
	std::cout << "nanogui screen created" << std::endl;
	std::cout << "initializing nanogui window" << std::endl;
	_screen->initialize(_win, true);
	std::cout << "nanogui window initialized, screen integrated with window" << std::endl;

	nanogui::FormHelper *gui = new nanogui::FormHelper(_screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Fuckyeah BITCH!");

	if (!this->_game->getSettings().getLastPlayer().empty())
		this->_game->loadPlayer(this->_game->getSettings().getLastPlayer());
	else
		newPlayer(); //function that uses nanogui to get the name of player and create player

	gui->addButton("A button", []() { std::cout << "Button pressed." << std::endl; });
	std::cout << "visualizing screen" << std::endl;
	_screen->setVisible(true);
	_screen->performLayout();
	nanoguiWindow->center();

	std::cout << "starting screen loop" << std::endl;
	while (!glfwWindowShouldClose(_win) && this->_game->getGameState() == GameState::MENU){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (_keyPressArr[ENTER]) {
			this->_game->setGameState(GameState::PLAY);
		}
		else if (_keyPressArr[ESC])
		{
			if (this->_game->getPlayState() == PlayState::GAME_PLAY)
				this->_game->setGameState(GameState::PLAY);
			else
				this->_game->setGameState(GameState::EXIT);
		}
		glfwGetFramebufferSize(_win, &_width, &_height);
		glViewport(0, 0, _width, _height);
		glClear(GL_COLOR_BUFFER_BIT);

		_screen->drawContents();
		_screen->drawWidgets();
		glfwSwapBuffers(_win);
	}
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
		if (clickX >= 360  && clickX <= 450 && clickY >= 300 && clickY <= 325)
			if (_mouseX >= 360  && _mouseX <= 450 && _mouseY >= 300 && _mouseY <= 325)
				std::cout << "'FUCK YEAH' Button pressed" << std::endl;
	}
}

void			Core::fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Press any key to exit" << std::endl;
	int temp;
	std::cin >> temp;
	std::exit(1);
}

void			Core::newPlayer() {
	this->_game->setPlayer(new Player("Bob"));
}

void			Core::initPlay() {
	std::cout << "playing" << std::endl;
	if (_keyPressArr[ESC])
		this->_game->setGameState(GameState::MENU);
}

void			Core::load() {

}

void			Core::settings() {

}

void			Core::save() {

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

bool			*Core::getKeyPressArr() {
	return (this->_keyPressArr);
}

void			Core::setKeyPressArr(bool newUp, bool newDown, bool newLeft, bool newRight, bool newSpace, bool newEnter, bool newEsc){
	this->_keyPressArr[UP] = newUp;
	this->_keyPressArr[DOWN] = newDown;
	this->_keyPressArr[LEFT] = newLeft;
	this->_keyPressArr[RIGHT] = newRight;
	this->_keyPressArr[SPACE] = newSpace;
	this->_keyPressArr[ENTER] = newEnter;
	this->_keyPressArr[ESC] = newEsc;
}
