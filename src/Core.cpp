#include <Core.hpp>

Core::Core() : _win(nullptr) {
	std::cout << "Constructing Core\n";
	this->_game = new Game;
	Settings settings = this->_game->getSettings();
	this->_width = settings.getResolutionX();
	this->_height = settings.getResolutionY();
	std::cout << "Core Constructed\n";
}

Core::Core(Core const & src) {
	std::cout << "Core Copy-Constructed\n";
	*this = src;
}

Core::~Core() {
	std::cout << "De-Constructing Core\n";
	delete this->_game;
	this->_game = nullptr;
	std::cout << "SDL is closed" << std::endl;
	SDL_Quit();
	std::cout << "Core De-Constructed\n";
}

Core &		Core::operator=(Core const & src) {
	this->_win = src.getWin();
	this->_game = src.getGame();
	this->_width = src.getWidth();
	this->_height = src.getHeight();
	return (*this);
}

SDL_Window	*Core::getWin() const {
	return (this->_win);
}

void		Core::setWin(SDL_Window	*newWin) {
	this->_win = newWin;
}

Game		*Core::getGame() const {
	return (this->_game);
}

void		Core::setGame(Game *newGame) {
	this->_game = newGame;
}

int			Core::getWidth() const {
	return (this->_width);
}

void		Core::setWidth(const int newWidth) {
	this->_width = newWidth;
}

int			Core::getHeight() const {
	return (this->_height);
}

void		Core::setHeight(const int newHeight) {
	this->_height = newHeight;
}

void		Core::run() {
	init();
	gameLoop();
}

void		Core::init() {
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

void		Core::input() {
	SDL_Event evnt;
	const Uint8*	keyPressArr = SDL_GetKeyboardState(NULL); // var to hold the current keypress, SEE https://wiki.libsdl.org/SDL_GetKeyboardState (Liam)

	keys     keyName;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
			case SDL_QUIT :
			this->_game->setState(GameState::EXIT);
			break;
			case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
		keyName = getAsciiKey(keyPressArr);
		switch (keyName) {
			case keys::LEFT :
			std::cout << "LEFTKEY!" << std::endl;
			break;
			case keys::RIGHT :
			std::cout << "RIGHTKEY!" << std::endl;
			break;
			case keys::UP :
			std::cout << "UPKEY!" << std::endl;
			break;
			case keys::DOWN :
			std::cout << "DOWNKEY!" << std::endl;
			break;
			case keys::SPACE :
			std::cout << "SPACEKEY!" << std::endl;
			break;
			case keys::ENTER :
			std::cout << "ENTERKEY!" << std::endl;
			break;
			case keys::ESC :
			std::cout << "ESCAPEKEY!" << std::endl;
			break;
			case keys::NONE :
			std::cout << "NONE" << std::endl;
			break;

		}
	}
}

void		Core::gameLoop() {
	while (this->_game->getState() != GameState::EXIT) {
		input();
		drawGame();
	}
}

void		Core::drawGame() {
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapWindow(_win);
}

keys		Core::getAsciiKey(const Uint8*	keyPressArr){
	if (keyPressArr[SDL_SCANCODE_LEFT])
		return keys::LEFT;
	else if (keyPressArr[SDL_SCANCODE_RIGHT])
		return keys::RIGHT;
	else if (keyPressArr[SDL_SCANCODE_UP])
		return keys::UP;
	else if (keyPressArr[SDL_SCANCODE_DOWN])
		return keys::DOWN;
	else if (keyPressArr[SDL_SCANCODE_SPACE])
		return keys::SPACE;
	else if (keyPressArr[SDL_SCANCODE_RETURN])
		return keys::ENTER;
	else if (keyPressArr[SDL_SCANCODE_ESCAPE])
		return keys::ESC;
	else
		return keys::NONE;
}


void		Core::fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Press any key to exit" << std::endl;
	int temp;
	std::cin >> temp;
	SDL_Quit();
	exit(1);
}
