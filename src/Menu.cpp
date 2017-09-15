#include <Menu.hpp>

nanogui::Screen *screen = nullptr;

Menu::Menu(int passedWidth, int passedHeight, Game *passedGame, GLFWwindow **passedWin) : _width(passedWidth), _height(passedHeight), _game(passedGame), _win(passedWin) {
	std::cout << "Constructing Menu\n";
	this->_menuState = MenuState::PLAYER_SELECT;
	this->_minimumTime = 50;
	std::cout << "Menu Constructed\n";
}

Menu::Menu(Menu const & src) {
	std::cout << "Menu Copy-Constructed\n";
	*this = src;
}

Menu &			Menu::operator=(Menu const & src) {
	for (int i = 0; i < 7; i++) {
		this->_keyPressArr[i] = src.getKeyPressArr(i);
	}
	this->_mouseX = src.getMouseX();
	this->_mouseY = src.getMouseY();
	this->_menuState = src.getMenuState();
	this->_delayTimer = src.getDelayTimer();
	this->_minimumTime = src.getMinimumTime();
	this->_width = src.getWidth();
	this->_height = src.getHeight();
	this->_game = src.getGame();
	this->_win = src.getWin();
	this->_settings = src.getSettings();


	return (*this);
}

Menu::~Menu() {
	std::cout << "De-Constructing Menu\n";
	std::cout << "closing nanogui screen" << std::endl;
	nanogui::shutdown();
	std::cout << "nanogui screen closed successfully" << std::endl;
	glfwTerminate();
	std::cout << "Menu De-Constructed\n";
}


void			Menu::menu() {
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
    screen->initialize(*_win, true);
    std::cout << "nanogui window initialized, screen integrated with window" << std::endl;

    glfwSetCursorPosCallback(*_win, [](GLFWwindow *, double x, double y) {
        screen->cursorPosCallbackEvent(x, y); }
    );
    glfwSetMouseButtonCallback(*_win, [](GLFWwindow *, int button, int action, int modifiers) {
        screen->mouseButtonCallbackEvent(button, action, modifiers); }
    );
    glfwSetKeyCallback(*_win, [](GLFWwindow *, int key, int scancode, int action, int mods) {
        screen->keyCallbackEvent(key, scancode, action, mods); }
    );
    glfwSetCharCallback(*_win, [](GLFWwindow *, unsigned int codepoint) {
        screen->charCallbackEvent(codepoint); }
    );

    while (this->_game->getGameState() == GameState::MENU) {
        switch (_menuState) {
            case MenuState::PLAYER_SELECT :
                playerSelectMenu();
                break;
            case MenuState::MAIN_MENU :
                mainMenu();
                break;
            case MenuState::LOAD_SAVE :
                break;
            case MenuState::SETTINGS :
                settingsMenu();
                break;
            case MenuState::KEYBINDING :
                keyBindingButton();
                break;
            case MenuState::PAUSE :
                pauseMenu();
                break;
            case MenuState::NO_MENU :
                break;
        }
    }
}

void			Menu::playerSelectMenu() {
	nanogui::FormHelper				*gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window>	nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), "Player Select");
	nanogui::Button					*b = new nanogui::Button(nanoguiWindow, "Plain button");
	std::vector<std::string>		playerNames = this->_game->checkPlayers();
	std::string						playerNameInput = "Enter your name";

	b->setVisible(false);
	nanoguiWindow->setLayout(new nanogui::GroupLayout);
	nanogui::Widget *tools = new nanogui::Widget(nanoguiWindow);
	tools->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Horizontal, nanogui::Alignment::Middle, 0, 6));

	if (playerNames.size() > 0) {
		for (std::vector<std::string>::iterator it = playerNames.begin(); it != playerNames.end(); ++it) {
			b = new nanogui::Button(tools, (*it).c_str());
			b->setCallback([&] {
				this->_game->setPlayer(Player(b->caption()));
				_menuState = MenuState::MAIN_MENU;
			});
		}
	}
	gui->addVariable("New Player", playerNameInput);
	gui->addButton("Create", [this, &playerNameInput]() {
		createButton(playerNameInput);
	});
	gui->addButton("Exit", [this]() {
		exitButton();
	});
	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::PLAYER_SELECT){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (_keyPressArr[ENTER])
			createButton(playerNameInput);
		else if (_keyPressArr[ESC] && getDelayTimer() >= getMinimumTime()) {
			exitButton();
		}
		renderMenu();
	}
	std::cout << "PLAYER NAME IS: " << playerNameInput << std::endl;
	if (glfwWindowShouldClose(*_win))
		this->_game->setGameState(GameState::EXIT);
	nanoguiWindow->dispose();
}

void            Menu::mainMenu() {

	nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(100, 100), this->_game->getPlayer().getName() + "'s Account");

	std::cout << *_game << std::endl;

	gui->addButton("New Game", [this]() {
		newGameButton();
	});


	if (this->_game->getHasSave())
		gui->addButton("Load Game", [this]() {
			loadGameButton();
		});
	else
		gui->addButton("Load Game", []() { std::cout << "NO SAVES" << std::endl; })->setEnabled(false);

	gui->addButton("Change Player", [this]() {
		playerSelectButton();
	})->setBackgroundColor(Eigen::Vector4i(57, 62, 25, 255));

	gui->addButton("Settings", [this]() {
		settingsButton();
	});

	gui->addButton("Exit", [this] {
		exitButton();
	});

	std::cout << "visualizing screen" << std::endl;
	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();

	std::cout << "starting screen loop" << std::endl;
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::MAIN_MENU){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (_keyPressArr[ESC] && getDelayTimer() >= getMinimumTime()) {
			playerSelectMenu();
		}
		else if (_keyPressArr[ENTER] && getDelayTimer() >= getMinimumTime()) {
			newGameButton();
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(*_win))
		exitButton();
	nanoguiWindow->dispose();
}

void			Menu::settingsMenu() {
    nanogui::FormHelper             *gui = new nanogui::FormHelper(screen);
    nanogui::ref<nanogui::Window>   nanoguiWindow = gui->addWindow(Eigen::Vector2i(2000, 2000), "SETTINGS");
    nanogui::Button                 *b = new nanogui::Button(nanoguiWindow, "Plain button");
    bool                            windowed;
    Settings                        tempSettings(this->_game->getSettings());

    std::cout << *_game << std::endl;
    std::cout << "_________________________________________________________________________________" << std::endl;
    std::cout << tempSettings << std::endl;

    b->setVisible(false);
    nanoguiWindow->setLayout(new nanogui::GroupLayout);

    new nanogui::Label(nanoguiWindow, "Windowed :");
    nanogui::CheckBox *cb = new nanogui::CheckBox(nanoguiWindow, "", [&tempSettings](bool state) {
        tempSettings.setWindowed(state);
    });
    cb->setChecked(_game->getSettings().getWindowed());

    new nanogui::Label(nanoguiWindow, "Resolution :    (requires restart)");
    nanogui::ComboBox *cobo = new nanogui::ComboBox(nanoguiWindow, { "800x600", "1280x800", "1920x1080" });
    switch (tempSettings.getResolution().first) {
        case 800 :
            cobo->setSelectedIndex(0);
            break;
        case 1280 :
            cobo->setSelectedIndex(1);
            break;
        case 1920 :
            cobo->setSelectedIndex(2);
            break;
    }

    new nanogui::Label(nanoguiWindow, "SFX Volume :");
    nanogui::Widget                 *panel = new nanogui::Widget(nanoguiWindow);
    panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Horizontal, nanogui::Alignment::Middle, 0, 20));
    nanogui::Slider *sliderSfx = new nanogui::Slider(panel);
    sliderSfx->setFixedWidth(100);
    sliderSfx->setValue(tempSettings.getFXVol());
    nanogui::TextBox *textBoxSfx = new nanogui::TextBox(panel);
    textBoxSfx->setFixedSize(nanogui::Vector2i(60, 25));
    textBoxSfx->setValue(std::to_string((int) (tempSettings.getFXVol())));
    textBoxSfx->setUnits("%");
    sliderSfx->setCallback([textBoxSfx, &tempSettings](float sfxVolume) {
        textBoxSfx->setValue(std::to_string((int) (sfxVolume * 100)));
        tempSettings.setFXVol((int) (sfxVolume * 100));
    });
    textBoxSfx->setAlignment(nanogui::TextBox::Alignment::Right);

    new nanogui::Label(nanoguiWindow, "Music Volume :");
    panel = new nanogui::Widget(nanoguiWindow);
    panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Horizontal, nanogui::Alignment::Middle, 0, 20));
    nanogui::Slider *sliderMusic = new nanogui::Slider(panel);
    nanogui::TextBox *textBoxMusic = new nanogui::TextBox(panel);
    sliderMusic->setFixedWidth(100);
    sliderMusic->setValue(tempSettings.getMusicVol());
    textBoxMusic->setFixedSize(nanogui::Vector2i(60, 25));
    textBoxMusic->setValue(std::to_string((int) (tempSettings.getMusicVol())));
    textBoxMusic->setUnits("%");
    sliderMusic->setCallback([textBoxMusic, &tempSettings](float musicVolume) {
        textBoxMusic->setValue(std::to_string((int) (musicVolume * 100)));
        tempSettings.setMusicVol((int) (musicVolume * 100));
    });
    textBoxMusic->setAlignment(nanogui::TextBox::Alignment::Right);

	nanogui::Widget *keyBindTools = new nanogui::Widget(nanoguiWindow);
	keyBindTools->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Horizontal, nanogui::Alignment::Middle, 0, 2));
	b = new nanogui::Button(keyBindTools, "Set Keybindings");
	b->setCallback([&]{
		keyBindingButton();
	});
	b->setFixedWidth(190);
    gui->addButton("Reset to default", [this, &cb, &sliderSfx, &textBoxSfx, &sliderMusic, &textBoxMusic]() {
        cb->setChecked(false);
        textBoxSfx->setValue("100");
        sliderMusic->setValue(100);
        textBoxMusic->setValue("100");
    });
    nanogui::Widget *tools = new nanogui::Widget(nanoguiWindow);
    tools->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Horizontal, nanogui::Alignment::Middle, 0, 2));
    b = new nanogui::Button(tools, "Return to menu");
    b->setCallback([&]{
        if (this->_game->getPlayState() == PlayState::GAME_PLAY) {
            std::cout << "accepted changes 1" << std::endl;
            _menuState = MenuState::PAUSE;
        }
        else {
            std::cout << "accepted changes 2" << std::endl;
            quitToMenuButton();
        }
    });
    b = new nanogui::Button(tools, "Apply");
    b->setCallback([&]{
        switch (cobo->selectedIndex()) {
            case 0 :
                tempSettings.setResolution(std::make_pair(800, 600));
                break;
            case 1 :
                tempSettings.setResolution(std::make_pair(1280, 800));
                break;
            case 2 :
                tempSettings.setResolution(std::make_pair(1920, 1080));
                break;
        }
        this->_game->setSettings(tempSettings);
        std::cout << tempSettings << std::endl << "Changes applied" << std::endl;
    });
    screen->setVisible(true);
    screen->performLayout();
    nanoguiWindow->center();
    resetDelayTimer();
    while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::SETTINGS){
        glfwPollEvents();
        updateKeys();
        updateMouse();
        if (_keyPressArr[ESC] && getDelayTimer() >= getMinimumTime())
        {
            if (this->_game->getPlayState() == PlayState::GAME_PLAY)
                _menuState = MenuState::PAUSE;
            else
                _menuState = MenuState::MAIN_MENU;
        }
        renderMenu();
    }
    if (glfwWindowShouldClose(*_win))
        exitButton();
    nanoguiWindow->dispose();
}

void            Menu::keyBindingMenu() {
    nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
    nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), "SET KEYBINDINGS");

	nanogui::Widget *upTools = new nanogui::Widget(nanoguiWindow);
    upTools->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Horizontal, nanogui::Alignment::Middle, 0, 2));
	new nanogui::Label(upTools, "Forward");
	nanogui::Button *upButton = new nanogui::Button(upTools, "W");
    upButton->setCallback([&]{

    });

    screen->setVisible(true);
    screen->performLayout();
    nanoguiWindow->center();
    resetDelayTimer();
    while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::PAUSE){
        glfwPollEvents();
        updateKeys();
        updateMouse();
        if (_keyPressArr[ENTER] && getDelayTimer() >= getMinimumTime())
            _menuState = MenuState::SETTINGS;
        renderMenu();
    }
    if (glfwWindowShouldClose(*_win))
        exitButton();
    nanoguiWindow->dispose();
}

void            Menu::pauseMenu() {
	nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), "PAUSED");

	gui->addButton("Resume", [this] {
		resumeButton();
	});

	gui->addButton("Settings", [this] {
		settingsButton();
	});

	gui->addButton("Quit to Menu", [this] {
		quitToMenuButton();
	});

	gui->addButton("Exit Program", [this] {
		exitButton();
	});

	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::PAUSE){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (_keyPressArr[ENTER] && getDelayTimer() >= getMinimumTime())
		{
			_menuState = MenuState::NO_MENU;
			this->_game->setGameState(GameState::PLAY);
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(*_win))
		exitButton();
	nanoguiWindow->dispose();
}

void			Menu::updateKeys() {
	int		state;
	bool	pressed = false;

	state = glfwGetKey(*_win, GLFW_KEY_LEFT);
	if (state == GLFW_PRESS)
		_keyPressArr[LEFT] = true;
	else
		_keyPressArr[LEFT] = false;
	state = glfwGetKey(*_win, GLFW_KEY_RIGHT);
	if (state == GLFW_PRESS)
		_keyPressArr[RIGHT] = true;
	else
		_keyPressArr[RIGHT] = false;
	state = glfwGetKey(*_win, GLFW_KEY_UP);
	if (state == GLFW_PRESS)
		_keyPressArr[UP] = true;
	else
		_keyPressArr[UP] = false;
	state = glfwGetKey(*_win, GLFW_KEY_DOWN);
	if (state == GLFW_PRESS)
		_keyPressArr[DOWN] = true;
	else
		_keyPressArr[DOWN] = false;
	state = glfwGetKey(*_win, GLFW_KEY_SPACE);
	if (state == GLFW_PRESS)
		_keyPressArr[SPACE] = true;
	else
		_keyPressArr[SPACE] = false;
	state = glfwGetKey(*_win, GLFW_KEY_ENTER);
	if (state == GLFW_PRESS)
		_keyPressArr[ENTER] = true;
	else
		_keyPressArr[ENTER] = false;
	state = glfwGetKey(*_win, GLFW_KEY_ESCAPE);
	if (state == GLFW_PRESS)
		_keyPressArr[ESC] = true;
	else
		_keyPressArr[ESC] = false;
}

void			Menu::updateMouse() {
	int				state;
	static bool		wasClicked = false;
	static double	clickX;
	static double	clickY;

	glfwGetCursorPos(*_win, &_mouseX, &_mouseY);
	state = glfwGetMouseButton(*_win, GLFW_MOUSE_BUTTON_1);
	if (state == GLFW_PRESS && wasClicked == false) {
		this->_game->getSound().playMenuClick();
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

bool            Menu::checkPlayerNameAvailability(std::string playerNameInputVar) {
	std::vector<std::string> 			playerNames = this->_game->checkPlayers();

	if (playerNameInputVar == "Enter your name")
		return (false);
	if (playerNames.size() > 0) {
		for (std::vector<std::string>::iterator it = playerNames.begin(); it != playerNames.end(); ++it) {
			if (!iequals(*it, playerNameInputVar))
				return (false);
		}
	}
	return (true);
}

bool 			Menu::iequals(const std::string& a, const std::string& b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i) {
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	}
	return true;
}

void			Menu::createButton(std::string playerNameInputVar) {
	std::cout << "Create new player pressed" << std::endl;
	if (checkPlayerNameAvailability(playerNameInputVar)) {
		this->_game->setPlayer(Player(playerNameInputVar));
		_menuState = MenuState::MAIN_MENU;
		std::cout << "Player : " << playerNameInputVar << " created" << std::endl;
	}
	else
		std::cout << "name not available: " << playerNameInputVar << std::endl;
}

void			Menu::exitButton() {
	this->_game->setGameState(GameState::EXIT);
	_menuState = MenuState::NO_MENU;
}

void            Menu::newGameButton() {
	std::cout << "New Game pressed." << std::endl;
	this->_game->setGameState(GameState::PLAY);
	this->_game->setPlayState(PlayState::GAME_PLAY);
	_menuState = MenuState::NO_MENU;
}

void            Menu::loadGameButton() {
	std::cout << "HAS SAVES" << std::endl;
}

void            Menu::playerSelectButton() {
	std::cout << "Change Player pressed." << std::endl;
	_menuState = MenuState::PLAYER_SELECT;
}

void            Menu::settingsButton() {
	std::cout << "Settings pressed." << std::endl;
	_menuState = MenuState::SETTINGS;
}

void            Menu::keyBindingButton() {
    std::cout << "keybinding menu" << std::endl;
    _menuState = MenuState ::KEYBINDING;
}

void            Menu::resumeButton() {
	this->_game->setGameState(GameState::PLAY);
	_menuState = MenuState::NO_MENU;
}

void            Menu::quitToMenuButton() {
	_menuState = MenuState::MAIN_MENU;
	this->_game->setGameState(GameState::MENU);
	this->_game->setPlayState(PlayState::GAME_LOAD);
}

void			Menu::renderMenu() {
	glfwGetFramebufferSize(*_win, &_width, &_height);
	glViewport(0, 0, _width, _height);
	glClear(GL_COLOR_BUFFER_BIT);

	screen->drawContents();
	screen->drawWidgets();
	glfwSwapBuffers(*_win);
	incrementDelayTimer();
}

double			Menu::getMouseX() const {
	return (this->_mouseX);
}

void			Menu::setMouseX(const double newMouseX) {
	this->_mouseX = newMouseX;
}

double			Menu::getMouseY() const {
	return (this->_mouseY);
}

void			Menu::setMouseY(const double newMouseY) {
	this->_mouseY = newMouseY;
}

bool			Menu::getKeyPressArr(const int index) const {
	return (this->_keyPressArr[index]);
}

void			Menu::setKeyPressArr(const int index, const bool newChoice){
	this->_keyPressArr[index] = newChoice;
}

MenuState		Menu::getMenuState() const {
	return (this->_menuState);
}

void			Menu::setMenuState(const MenuState newMenuState){
	this->_menuState = newMenuState;
}

double			Menu::getDelayTimer() const {
	return (this->_delayTimer);
}

void 			Menu::resetDelayTimer() {
	this->_delayTimer = 0;
}

void			Menu::incrementDelayTimer() {
	this->_delayTimer++;
}

double			Menu::getMinimumTime() const {
	return (this->_minimumTime);
}
void			Menu::setMinimumTime(const double newMinimumTime) {
	this->_minimumTime = newMinimumTime;
}

Game			*Menu::getGame() const {
	return (this->_game);
}

void			Menu::setGame(Game *newGame) {
	this->_game = newGame;
}

GLFWwindow		**Menu::getWin() const {
	return (this->_win);
}

void			Menu::setWin(GLFWwindow **win) {
	this->_win = win;
}

int				Menu::getWidth() const {
	return (this->_width);
}

void			Menu::setWidth(const int newWidth) {
	this->_width = newWidth;
}

int				Menu::getHeight() const {
	return (this->_height);
}

void			Menu::setHeight(const int newHeight) {
	this->_height = newHeight;
}

Settings		*Menu::getSettings() const {
	return (this->_settings);
}

void			Menu::setSettings(Settings *newSettings){
	this->_settings = newSettings;
}