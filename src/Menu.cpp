#include <Menu.hpp>

nanogui::Screen *screen = nullptr;

Menu::Menu(int passedWidth, int passedHeight, Game *passedGame, GLFWwindow **passedWin) : _menuState(MenuState::PLAYER_SELECT), _minimumTime(10), _width(passedWidth), _height(passedHeight), _game(passedGame), _win(passedWin) {
	std::cout << "Menu Constructed\n";
}

Menu::Menu(Menu const & src) {
	std::cout << "Menu Copy-Constructed\n";
	*this = src;
}

Menu &			Menu::operator=(Menu const & src) {
	this->_mouseX = src.getMouseX();
	this->_mouseY = src.getMouseY();
	this->_menuState = src.getMenuState();
	this->_delayTimer = src.getDelayTimer();
	this->_minimumTime = src.getMinimumTime();
	this->_width = src.getWidth();
	this->_height = src.getHeight();
	this->_game = src.getGame();
	this->_win = src.getWin();
	return (*this);
}

Menu::~Menu() {
	nanogui::shutdown();
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
	screen = new nanogui::Screen;
	screen->initialize(*_win, true);
	glfwSetCursorPosCallback(*_win, [](GLFWwindow *, double x, double y) {
		screen->cursorPosCallbackEvent(x, y);
	});
	glfwSetMouseButtonCallback(*_win, [](GLFWwindow *, int button, int action, int modifiers) {
		screen->mouseButtonCallbackEvent(button, action, modifiers);
	});
	glfwSetKeyCallback(*_win, [](GLFWwindow *, int key, int scancode, int action, int mods) {
		screen->keyCallbackEvent(key, scancode, action, mods);
	});
	glfwSetCharCallback(*_win, [](GLFWwindow *, unsigned int codepoint) {
		screen->charCallbackEvent(codepoint);
	});

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
				keyBindingMenu();
				break;
			case MenuState::PAUSE :
				pauseMenu();
				break;
			case MenuState::DIFFICULTY :
				difficultyMenu();
				break;
			case MenuState::LEVEL_FAIL :
				break;
			case MenuState::LEVEL_PASS :
				break;
			case MenuState::NO_MENU :
				break;
		}
	}
}

void			Menu::errorPopup(const std::string & title, const std::string & message, const std::string & btnText) {
	nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), title);
	auto breaker = false;

	nanoguiWindow->setLayout(new nanogui::GroupLayout);
	new nanogui::Label(nanoguiWindow, message);
	gui->addButton(btnText, [&breaker] {
		breaker = true;
	});

	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();
	_game->getSound().playMenuFail();
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && !breaker){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if ((glfwGetKey(*_win, GLFW_KEY_ENTER) == GLFW_PRESS || (glfwGetKey(*_win, GLFW_KEY_ESCAPE) == GLFW_PRESS)) && getDelayTimer() >= getMinimumTime()) {
			breaker = true;
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(*_win))
		exitButton();
	nanoguiWindow->dispose();
}

void			Menu::playerSelectMenu() {
	glfwSetWindowPos(*(_win), this->_game->getSettings().getXPos(), this->_game->getSettings().getYPos());
	nanogui::FormHelper				*gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window>	nanoguiWindow = gui->addWindow(Eigen::Vector2i(100, 100), "Player Select");
	std::vector<std::string>		playerNames = this->_game->checkPlayers();
	std::string						playerNameInput = "Enter your name";
	int								fixedWidthHolder = 150;
	static int 						index = 1;
	bool 							breaker = false;

	nanoguiWindow->setLayout(new nanogui::GroupLayout);
	gui->addVariable("New Player :", playerNameInput)->setFixedWidth(fixedWidthHolder);
	nanogui::Widget *tools = new nanogui::Widget(nanoguiWindow);
	tools->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 0));
	nanogui::Button *CreatePlayerBtn = new nanogui::Button(tools, "Create New Player");
	CreatePlayerBtn->setCallback([&] {
		std::cout << "In Create New Player Btn Callback\n";
		createButton(playerNameInput);
	});
	if (index == 1)
		CreatePlayerBtn->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));
	CreatePlayerBtn->setFixedWidth(fixedWidthHolder);
	if (playerNames.size() > 0) {
		new nanogui::Label(nanoguiWindow, "");
		new nanogui::Label(nanoguiWindow, "Choose an Existing Player :");
	}
	nanogui::ComboBox *playerCobo = new nanogui::ComboBox(nanoguiWindow, playerNames);
	playerCobo->setFixedWidth(fixedWidthHolder);
	if (playerNames.size() > 0) {
		playerCobo->setFixedWidth(fixedWidthHolder);
		nanogui::Widget *tools = new nanogui::Widget(nanoguiWindow);
		tools->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Horizontal, nanogui::Alignment::Middle, 0, 2));
		nanogui::Button *b = new nanogui::Button(tools, "Select");
		b->setCallback([&]{
			selectButton(playerNames, playerCobo->selectedIndex());
		});
		if (index == 2)
			b->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));
		b->setFixedWidth(fixedWidthHolder / 2 - 1);
		b = new nanogui::Button(tools, "Delete");
		b->setCallback([&]{
			deleteButton(playerNames, playerCobo->selectedIndex());
			breaker = true;
			playerNames = this->_game->checkPlayers();
			if (playerNames.empty())
				index = 1;
		});
		if (index == 3)
			b->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));
		b->setFixedWidth(fixedWidthHolder / 2 - 1);
	}
	else
		playerCobo->setVisible(false);
	tools = new nanogui::Widget(nanoguiWindow);
	tools->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Horizontal, nanogui::Alignment::Fill, 10, 6));
	new nanogui::Label(tools, "");
	tools = new nanogui::Widget(nanoguiWindow);
	tools->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Horizontal, nanogui::Alignment::Fill, 0, 6));
	nanogui::Button *exitGameButton = new nanogui::Button(tools, "Exit");
	exitGameButton->setCallback([this]{
		exitButton();
	});
	if (index == 4)
		exitGameButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));
	exitGameButton->setFixedWidth(fixedWidthHolder);
	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::PLAYER_SELECT && !breaker) {
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (getDelayTimer() >= getMinimumTime()) {
			if (playerNames.empty()) {
				if (index != 1 && index != 4)
					index = 1;
				if (checkMenuSelectionKeys() != 0) {
					if (index == 1)
						index = 4;
					else
						index = 1;
					breaker = true;
					this->_game->getSound().playMenuKeypress();
				}
			} else {
				if (checkMenuSelectionKeys() != 0) {
					index += checkMenuSelectionKeys();
					if (index > 4)
						index = 1;
					else if (index < 1)
						index = 4;
					breaker = true;
					this->_game->getSound().playMenuKeypress();
				}
			}
			if (glfwGetKey(*_win, GLFW_KEY_ENTER) == GLFW_PRESS) {
				switch (index) {
					case 1 :
						createButton(playerNameInput);
						break;
					case 2 :
						selectButton(playerNames, playerCobo->selectedIndex());
						break;
					case 3 :
						deleteButton(playerNames, playerCobo->selectedIndex());
						playerNames = this->_game->checkPlayers();
						breaker = true;
						index = 1;
						break;
					case 4 :
						exitButton();
						break;
				}
				breaker = true;
			} else if (this->_game->getKeyPressArr(ESCAPE) && getDelayTimer() >= getMinimumTime())
				exitButton();
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(*_win))
		this->_game->setGameState(GameState::EXIT);
	playerCobo->setVisible(false);
	nanoguiWindow->dispose();
}

void            Menu::mainMenu() {

	nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(100, 100), this->_game->getPlayer().getName() + "'s Account");
	static int 			index = 1;
	bool 				breaker = false;

	nanoguiWindow->setLayout(new nanogui::GroupLayout);
	nanogui::Button *b = new nanogui::Button(nanoguiWindow, "New Game");
	b->setCallback([this]{
		_menuState = MenuState::DIFFICULTY;
	});
	if (index == 1)
		b->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	b = new nanogui::Button(nanoguiWindow, "Continue");
	b->setCallback([this]{
		loadGameButton();
	});
	if (this->_game->getHasSave()) {
		b->setEnabled(false);
	}
	if (index == 2)
		b->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	b = new nanogui::Button(nanoguiWindow, "Settings");
	b->setCallback([this]{
		settingsButton();
	});
	if (index == 3)
		b->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	b = new nanogui::Button(nanoguiWindow, "Logout");
	b->setCallback([this]{
		logoutButton();
	});
	if (index == 4)
		b->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	b = new nanogui::Button(nanoguiWindow, "Exit");
	b->setCallback([this]{
		exitButton();
	});
	if (index == 5)
		b->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));


	std::cout << "visualizing screen" << std::endl;
	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();

	std::cout << "starting screen loop" << std::endl;
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::MAIN_MENU && !breaker){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (getDelayTimer() >= 10) {
			if (checkMenuSelectionKeys() != 0) {
				index += checkMenuSelectionKeys();
				if (index > 5)
					index = 1;
				if (index < 1)
					index = 5;
				breaker = true;
				this->_game->getSound().playMenuKeypress();
			}

			if (glfwGetKey(*_win, GLFW_KEY_ENTER))
				switch (index) {
					case 1 :
						_menuState = MenuState::DIFFICULTY;
						break;
					case 2 :
						if (this->_game->getHasSave())
							loadGameButton();
						else
							errorPopup("ERROR!", "No previous saved games.", "OK");
						break;
					case 3 :
						settingsButton();
						break;
					case 4 :
						logoutButton();
						break;
					case 5 :
						_game->getSound().playMenuClick();
						exitButton();
						break;

				}
			else if (this->_game->getKeyPressArr(ESCAPE)) {
				playerSelectButton();
				_game->getSound().playMenuClick();
			}
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(*_win))
		exitButton();
	nanoguiWindow->dispose();
}

void			Menu::settingsMenu() {
	nanogui::FormHelper             *gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window>   nanoguiWindow = gui->addWindow(Eigen::Vector2i(2000, 2000), "Settings");
	nanogui::Button                 *b = new nanogui::Button(nanoguiWindow, "Plain button");
	Settings                        tempSettings(this->_game->getSettings());
	static int						index = 1;
	bool							breaker = false;
	Settings                        buSettings(this->_game->getSettings());

	std::cout << *_game << std::endl;
	std::cout << "_________________________________________________________________________________" << std::endl;
	std::cout << tempSettings << std::endl;

	b->setVisible(false);
	nanoguiWindow->setLayout(new nanogui::GroupLayout);

	new nanogui::Label(nanoguiWindow, "Windowed :");

	nanogui::CheckBox *cb = new nanogui::CheckBox(nanoguiWindow, "", [&](bool state) {
		tempSettings.setWindowed(state);
		this->_game->setSettings(tempSettings);
		std::cout << "Changes applied" << std::endl;
	});
	cb->setChecked(tempSettings.getWindowed());

	new nanogui::Label(nanoguiWindow, "Resolution :");
	nanogui::ComboBox *cobo = new nanogui::ComboBox(nanoguiWindow, { "800x600", "1280x800", "1920x1080" });
	switch (tempSettings.getResolutionX()) {
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
	textBoxSfx->setValue(std::to_string((int) (tempSettings.getFXVol() * 100)));
	textBoxSfx->setUnits("%");
	sliderSfx->setCallback([&](float sfxVolume) {
		textBoxSfx->setValue(std::to_string((int) (sfxVolume * 100)));
		tempSettings.setFXVol(sfxVolume);
		this->_game->setSettings(tempSettings);
		std::cout << "Changes applied" << std::endl;
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
	textBoxMusic->setValue(std::to_string((int) (tempSettings.getMusicVol() * 100)));
	textBoxMusic->setUnits("%");
	sliderMusic->setCallback([&](float musicVolume) {
		textBoxMusic->setValue(std::to_string((int) (musicVolume * 100)));
		tempSettings.setMusicVol(musicVolume);
		this->_game->setSettings(tempSettings);
		std::cout << "Changes applied" << std::endl;
	});

	textBoxMusic->setAlignment(nanogui::TextBox::Alignment::Right);

	nanogui::Widget *keyBindTools = new nanogui::Widget(nanoguiWindow);
	keyBindTools->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Vertical, nanogui::Alignment::Middle, 0, 2));
	b = new nanogui::Button(keyBindTools, "Set Keybindings");
	b->setCallback([&]{
		_menuState = MenuState::KEYBINDING;
		_game->getSound().playMenuClick();
	});
	if (index == 1)
		b->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));
	b->setFixedWidth(180);
	b = new nanogui::Button(keyBindTools, "Reset to default");
	b->setCallback([&]{
		this->_game->setSettings(Settings());
		breaker = true;
		_game->getSound().playMenuClick();
	});
	if (index == 2)
		b->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));
	b->setFixedWidth(180);
	nanogui::Widget *tools = new nanogui::Widget(nanoguiWindow);
	tools->setLayout(new nanogui::BoxLayout(nanogui::Orientation ::Horizontal, nanogui::Alignment::Middle, 0, 2));
	b = new nanogui::Button(tools, "Cancel");
	b->setCallback([&]{
		this->_game->setSettings(buSettings);
		if (this->_game->getPlayState() == PlayState::GAME_PLAY) {
			_menuState = MenuState::PAUSE;
			_game->getSound().playMenuClick();
		}
		else
			quitToMenuButton();
	});
	if (index == 3)
		b->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));
	b->setFixedWidth(89);
	b = new nanogui::Button(tools, "Apply");
	b->setCallback([&]{
		applyButton(cobo->selectedIndex(), &tempSettings);
		_game->getSound().playMenuClick();
	});
	if (index == 4)
		b->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));
	b->setFixedWidth(89);
	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::SETTINGS && !breaker){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (getDelayTimer() >= 10) {
			if (checkMenuSelectionKeys() != 0) {
				index += checkMenuSelectionKeys();
				if (index > 4)
					index = 1;
				if (index < 1)
					index = 4;
				breaker = true;
				this->_game->getSound().playMenuKeypress();
			}
			if (glfwGetKey(*_win, GLFW_KEY_ENTER))
				switch (index) {
					case 1 :
						_game->getSound().playMenuClick();
						_menuState = MenuState::KEYBINDING;
						break;
					case 2 :
						this->_game->setSettings(Settings());
						_game->getSound().playMenuClick();
						break;
					case 3 :
						if (this->_game->getPlayState() == PlayState::GAME_PLAY) {
							_game->getSound().playMenuClick();
							_menuState = MenuState::PAUSE;
						}
						else
							quitToMenuButton();
					case 4 :
						_game->getSound().playMenuClick();
						applyButton(cobo->selectedIndex(), &tempSettings);
						break;
				}
			else if (this->_game->getKeyPressArr(ESCAPE)) {
				if (this->_game->getPlayState() == PlayState::GAME_PLAY)
					_menuState = MenuState::PAUSE;
				else
					_menuState = MenuState::MAIN_MENU;
				_game->getSound().playMenuClick();
			}
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(*_win))
		exitButton();
	nanoguiWindow->dispose();
}

void            Menu::keyBindingMenu() {
	bool 		breaker = false;
	static int 	index = 1;
	Settings tempSettings(this->_game->getSettings());
	nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), "PAUSED");
	nanogui::GridLayout *layout = new nanogui::GridLayout(nanogui::Orientation::Horizontal, 2,
														  nanogui::Alignment::Middle, 15, 10);
	layout->setColAlignment({nanogui::Alignment::Maximum, nanogui::Alignment::Fill});
	layout->setSpacing(0, 10);
	nanoguiWindow->setLayout(layout);

	BindingButtonState bindingButtonState = BindingButtonState::NONE;

	std::cout << "INDEX :" << index << std::endl;

	// UP
	new nanogui::Label(nanoguiWindow, "Up :");
	nanogui::Button *upKeyButton = new nanogui::Button(nanoguiWindow, "");
	upKeyButton->setVisible(false);
	if (checkForKeySymbol(_game->getSettings().getUpKey()) != 0)
		upKeyButton = nanoguiWindow->add<nanogui::Button>("", checkForKeySymbol(_game->getSettings().getUpKey()));
	else
		upKeyButton = nanoguiWindow->add<nanogui::Button>(findNameForBinding(_game->getSettings().getUpKey()));
	upKeyButton->setCallback([&, this] {
		upKeyButton->setCaption("");
		upKeyButton->setCaption("?");
		bindingButtonState = BindingButtonState::UP_BINDING;
		_game->getSound().playMenuClick();
	});
	if (index == 1)
		upKeyButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));


	// DOWN
	new nanogui::Label(nanoguiWindow, "Down :");
	nanogui::Button *downKeyButton = new nanogui::Button(nanoguiWindow, "");
	downKeyButton->setVisible(false);
	if (checkForKeySymbol(_game->getSettings().getDownKey()) != 0)
		downKeyButton = nanoguiWindow->add<nanogui::Button>("", checkForKeySymbol(_game->getSettings().getDownKey()));
	else
		downKeyButton = nanoguiWindow->add<nanogui::Button>(findNameForBinding(_game->getSettings().getDownKey()));
	downKeyButton->setCallback([&, this] {
		downKeyButton->setCaption("");
		downKeyButton->setCaption("?");
		bindingButtonState = BindingButtonState::DOWN_BINDING;
		_game->getSound().playMenuClick();
	});
	if (index == 2)
		downKeyButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	// LEFT
	new nanogui::Label(nanoguiWindow, "Left :");
	nanogui::Button *leftKeyButton = new nanogui::Button(nanoguiWindow, "");
	leftKeyButton->setVisible(false);
	if (checkForKeySymbol(_game->getSettings().getLeftKey()) != 0)
		leftKeyButton = nanoguiWindow->add<nanogui::Button>("", checkForKeySymbol(_game->getSettings().getLeftKey()));
	else
		leftKeyButton = nanoguiWindow->add<nanogui::Button>(findNameForBinding(_game->getSettings().getLeftKey()));
	leftKeyButton->setCallback([&, this] {
		leftKeyButton->setCaption("");
		leftKeyButton->setCaption("?");
		bindingButtonState = BindingButtonState::LEFT_BINDING;
		_game->getSound().playMenuClick();
	});
	if (index == 3)
		leftKeyButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	//RIGHT
	new nanogui::Label(nanoguiWindow, "Right :");
	nanogui::Button *rightKeyButton = new nanogui::Button(nanoguiWindow, "");
	rightKeyButton->setVisible(false);
	if (checkForKeySymbol(_game->getSettings().getRightKey()) != 0)
		rightKeyButton = nanoguiWindow->add<nanogui::Button>("", checkForKeySymbol(_game->getSettings().getRightKey()));
	else
		rightKeyButton = nanoguiWindow->add<nanogui::Button>(findNameForBinding(_game->getSettings().getRightKey()));
	rightKeyButton->setCallback([&, this] {
		rightKeyButton->setCaption("");
		rightKeyButton->setCaption("?");
		bindingButtonState = BindingButtonState::RIGHT_BINDING;
		_game->getSound().playMenuClick();
	});
	if (index == 4)
		rightKeyButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	//ACTION
	new nanogui::Label(nanoguiWindow, "Action :");
	nanogui::Button *actionKeyButton = new nanogui::Button(nanoguiWindow, "");
	actionKeyButton->setVisible(false);
	if (checkForKeySymbol(_game->getSettings().getActionKey()) != 0)
		actionKeyButton = nanoguiWindow->add<nanogui::Button>("", checkForKeySymbol(_game->getSettings().getActionKey()));
	else
		actionKeyButton = nanoguiWindow->add<nanogui::Button>(findNameForBinding(_game->getSettings().getActionKey()));
	actionKeyButton->setCallback([&, this] {
		actionKeyButton->setCaption("");
		actionKeyButton->setCaption("?");
		bindingButtonState = BindingButtonState::ACTION_BINDING;
		_game->getSound().playMenuClick();
	});
	if (index == 5)
		actionKeyButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	//ACCEPT
	new nanogui::Label(nanoguiWindow, "Accept :");
	nanogui::Button *acceptKeyButton = new nanogui::Button(nanoguiWindow, "");
	acceptKeyButton->setVisible(false);
	if (checkForKeySymbol(_game->getSettings().getAcceptKey()) != 0)
		acceptKeyButton = nanoguiWindow->add<nanogui::Button>("", checkForKeySymbol(_game->getSettings().getAcceptKey()));
	else
		acceptKeyButton = nanoguiWindow->add<nanogui::Button>(findNameForBinding(_game->getSettings().getAcceptKey()));
	acceptKeyButton->setCallback([&, this] {
		acceptKeyButton->setCaption("");
		acceptKeyButton->setCaption("?");
		bindingButtonState = BindingButtonState::ACCEPT_BINDING;
		_game->getSound().playMenuClick();
	});
	if (index == 6)
		acceptKeyButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	//ESCAPE
	new nanogui::Label(nanoguiWindow, "Escape :");
	nanogui::Button *escapeKeyButton = new nanogui::Button(nanoguiWindow, "");
	escapeKeyButton->setVisible(false);
	if (checkForKeySymbol(_game->getSettings().getEscapeKey()) != 0)
		escapeKeyButton = nanoguiWindow->add<nanogui::Button>("", checkForKeySymbol(_game->getSettings().getEscapeKey()));
	else
		escapeKeyButton = nanoguiWindow->add<nanogui::Button>(findNameForBinding(_game->getSettings().getEscapeKey()));
	escapeKeyButton->setCallback([&, this] {
		escapeKeyButton->setCaption("");
		escapeKeyButton->setCaption("?");
		bindingButtonState = BindingButtonState::ESCAPE_BINDING;
		_game->getSound().playMenuClick();
	});
	if (index == 7)
		escapeKeyButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	nanogui::Button *exitKeyBindingButton = nanoguiWindow->add<nanogui::Button>("Back");
	exitKeyBindingButton->setCallback([&] {
		_menuState = MenuState::SETTINGS;
		_game->getSound().playMenuClick();
		_game->getSound().playMenuClick();
	});
	if (index == 8)
		exitKeyBindingButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::KEYBINDING && !breaker) {
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (getDelayTimer() >= getMinimumTime()) {
			if (findKeyForBinding() != 0) {
				nanoguiWindow->setVisible(false);
				bindKeysWithoutConflicts(bindingButtonState, &tempSettings);
				nanoguiWindow->setVisible(true);
			}
			if (bindingButtonState != BindingButtonState::NONE) {
				if (findKeyForBinding() != 0) {
					_game->getSound().playMenuClick();
					this->_game->setSettings(tempSettings);
					this->_game->savePlayer();
					breaker = true;
				}

			} else {
				if (checkMenuSelectionKeys() != 0) {
					index += checkMenuSelectionKeys();
					if (index > 8)
						index = 1;
					if (index < 1)
						index = 8;
					breaker = true;
					this->_game->getSound().playMenuKeypress();
				}
				if (glfwGetKey(*_win, GLFW_KEY_ENTER)) {
					switch (index) {
						case 1 :
							upKeyButton->setCaption("");
							upKeyButton->setCaption("?");
							bindingButtonState = BindingButtonState::UP_BINDING;
							_game->getSound().playMenuClick();
							break;
						case 2 :
							downKeyButton->setCaption("");
							downKeyButton->setCaption("?");
							bindingButtonState = BindingButtonState::DOWN_BINDING;
							_game->getSound().playMenuClick();
							break;
						case 3 :
							leftKeyButton->setCaption("");
							leftKeyButton->setCaption("?");
							bindingButtonState = BindingButtonState::LEFT_BINDING;
							_game->getSound().playMenuClick();
							break;
						case 4 :
							rightKeyButton->setCaption("");
							rightKeyButton->setCaption("?");
							bindingButtonState = BindingButtonState::RIGHT_BINDING;
							_game->getSound().playMenuClick();
							break;
						case 5 :
							actionKeyButton->setCaption("");
							actionKeyButton->setCaption("?");
							bindingButtonState = BindingButtonState::ACTION_BINDING;
							_game->getSound().playMenuClick();
							break;
						case 6 :
							acceptKeyButton->setCaption("");
							acceptKeyButton->setCaption("?");
							bindingButtonState = BindingButtonState::ACCEPT_BINDING;
							_game->getSound().playMenuClick();
							break;
						case 7 :
							escapeKeyButton->setCaption("");
							escapeKeyButton->setCaption("?");
							bindingButtonState = BindingButtonState::ESCAPE_BINDING;
							_game->getSound().playMenuClick();
							break;
						case 8 :
							_menuState = MenuState::SETTINGS;
							_game->getSound().playMenuClick();
							break;
					}
					resetDelayTimer();
				}
				else if (this->_game->getKeyPressArr(ESCAPE)) {
					_menuState = MenuState::SETTINGS;
					_game->getSound().playMenuClick();
				}
			}
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(*_win))
		exitButton();
	nanoguiWindow->dispose();
}

int		Menu::checkMenuSelectionKeys() {
	if (glfwGetKey(*_win, GLFW_KEY_UP) == GLFW_PRESS) {
		//this->_game->getSound().playMenuKeypress();
		return (-1);
	}
	else if (glfwGetKey(*_win, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(*_win, GLFW_KEY_TAB) == GLFW_PRESS) {
		//this->_game->getSound().playMenuKeypress();
		std::cout << "just tab" << std::endl;
		return (1);
	}
	else
		return (0);
}

int		Menu::checkForKeySymbol(int keyPressed) {
	if (keyPressed == GLFW_KEY_UP)
		return (ENTYPO_ICON_UP);
	else if (keyPressed == GLFW_KEY_DOWN)
		return (ENTYPO_ICON_DOWN);
	else if (keyPressed == GLFW_KEY_LEFT)
		return (ENTYPO_ICON_LEFT);
	else if (keyPressed == GLFW_KEY_RIGHT)
		return (ENTYPO_ICON_RIGHT);
	else
		return (0);
}

int		Menu::findKeyForBinding() {
	for (int i = 65; i <= 90; i++) {
		if (glfwGetKey(*_win, i) == GLFW_PRESS)
			return (i);
	}
	if (glfwGetKey(*_win, GLFW_KEY_UP) == GLFW_PRESS)
		return (GLFW_KEY_UP);
	else if (glfwGetKey(*_win, GLFW_KEY_DOWN) == GLFW_PRESS)
		return (GLFW_KEY_DOWN);
	else if (glfwGetKey(*_win, GLFW_KEY_LEFT) == GLFW_PRESS)
		return (GLFW_KEY_LEFT);
	else if (glfwGetKey(*_win, GLFW_KEY_RIGHT) == GLFW_PRESS)
		return (GLFW_KEY_RIGHT);
	else if (glfwGetKey(*_win, GLFW_KEY_ENTER) == GLFW_PRESS)
		return (GLFW_KEY_ENTER);
	else if (glfwGetKey(*_win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		return (GLFW_KEY_ESCAPE);
	else if (glfwGetKey(*_win, GLFW_KEY_SPACE) == GLFW_PRESS)
		return (GLFW_KEY_SPACE);
	else if (glfwGetKey(*_win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		return (GLFW_KEY_LEFT_SHIFT);
	else if (glfwGetKey(*_win, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		return (GLFW_KEY_RIGHT_SHIFT);
	else if (glfwGetKey(*_win, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
		return (GLFW_KEY_BACKSPACE);

	return (0);
}

std::string		Menu::findNameForBinding(int keyPressed) {
	if (keyPressed == GLFW_KEY_ENTER)
		return ("Enter");
	else if (keyPressed == GLFW_KEY_ESCAPE)
		return ("ESC");
	else if (keyPressed == GLFW_KEY_SPACE)
		return ("Space");
	else if (keyPressed == GLFW_KEY_LEFT_SHIFT)
		return ("L Shift");
	else if (keyPressed == GLFW_KEY_RIGHT_SHIFT)
		return ("R Shift");
	else if (keyPressed == GLFW_KEY_BACKSPACE)
		return ("Backspace");
	else
		return (std::string(1, keyPressed));
}

void			Menu::bindKeysWithoutConflicts(BindingButtonState bindingButtonState, Settings *tempSettings) {
	int		c = findKeyForBinding();
	int 	boundIndex;
	
	if (c == tempSettings->getUpKey())
		boundIndex = 1;
	else if (c == tempSettings->getDownKey())
		boundIndex = 2;
	else if (c == tempSettings->getLeftKey())
		boundIndex = 3;
	else if (c == tempSettings->getRightKey())
		boundIndex = 4;
	else if (c == tempSettings->getAcceptKey())
		boundIndex = 5;
	else if (c == tempSettings->getActionKey())
		boundIndex = 6;
	else if (c == tempSettings->getEscapeKey())
		boundIndex = 7;
	else
		boundIndex = 0;
	
	switch (bindingButtonState) {
		case BindingButtonState::UP_BINDING :
			if (boundIndex == 0 || boundIndex == 1)
				tempSettings->setUpKey(c);
			else
				errorPopup("ERROR!", "Keybinding already in use.", "OK");
			break;
		case BindingButtonState::DOWN_BINDING :
			if (boundIndex == 0 || boundIndex == 2)
				tempSettings->setDownKey(c);
			else
				errorPopup("ERROR!", "Keybinding already in use.", "OK");
			break;
		case BindingButtonState::LEFT_BINDING :
			if (boundIndex == 0 || boundIndex == 3)
				tempSettings->setLeftKey(c);
			else
				errorPopup("ERROR!", "Keybinding already in use.", "OK");
			break;
		case BindingButtonState::RIGHT_BINDING :
			if (boundIndex == 0 || boundIndex == 4)
				tempSettings->setRightKey(c);
			else
				errorPopup("ERROR!", "Keybinding already in use.", "OK");
			break;
		case BindingButtonState::ACCEPT_BINDING :
			if (boundIndex == 0 || boundIndex == 5)
				tempSettings->setAcceptKey(c);
			else
				errorPopup("ERROR!", "Keybinding already in use.", "OK");
			break;
		case BindingButtonState::ACTION_BINDING :
			if (boundIndex == 0 || boundIndex == 6)
				tempSettings->setActionKey(c);
			else
				errorPopup("ERROR!", "Keybinding already in use.", "OK");
			break;
		case BindingButtonState::ESCAPE_BINDING :
			if (boundIndex == 0 || boundIndex == 7)
				tempSettings->setEscapeKey(c);
			else
				errorPopup("ERROR!", "Keybinding already in use.", "OK");
			break;
		case BindingButtonState::NONE :
			break;
	}
}

void            Menu::pauseMenu() {
	nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), "PAUSED");
	static int 			index = 1;
	bool 				breaker = false;

	nanoguiWindow->setLayout(new nanogui::GroupLayout);
	nanogui::Button *nanoResumeButton = nanoguiWindow->add<nanogui::Button>("Resume");
	nanoResumeButton->setCallback([&] {
		resumeButton();
	});
	if (index == 1)
		nanoResumeButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));


	nanogui::Button *nanoSettingsButton = nanoguiWindow->add<nanogui::Button>("Settings");
	nanoSettingsButton->setCallback([&] {
		settingsButton();
	});
	if (index == 2)
		nanoSettingsButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));
	
	nanogui::Button *nanoQuitToMenuButton = nanoguiWindow->add<nanogui::Button>("Quit To Menu");
	nanoQuitToMenuButton->setCallback([&] {
		quitToMenuButton();
	});
	if (index == 3)
		nanoQuitToMenuButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	nanogui::Button *nanoExitButton = nanoguiWindow->add<nanogui::Button>("Exit Program");
	nanoExitButton->setCallback([&] {
		exitButton();
	});
	if (index == 4)
		nanoExitButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::PAUSE && !breaker){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (getDelayTimer() >= 10) {
			if (checkMenuSelectionKeys() != 0) {
				index += checkMenuSelectionKeys();
				if (index > 4)
					index = 1;
				if (index < 1)
					index = 4;
				breaker = true;
				this->_game->getSound().playMenuKeypress();
			}

			if (glfwGetKey(*_win, GLFW_KEY_ENTER))
				switch (index) {
					case 1 :
						resumeButton();
						break;
					case 2 :
						settingsButton();
						break;
					case 3 :
						quitToMenuButton();
						break;
					case 4 :
						exitButton();
						break;
				}
			else if (this->_game->getKeyPressArr(ESCAPE)) {
				playerSelectButton();
				_game->getSound().playMenuClick();
			}
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(*_win))
		exitButton();
	nanoguiWindow->dispose();
}

void 			Menu::difficultyMenu() {
	nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), "Difficulty");
	static int 			index = 1;
	bool 				breaker = false;

	nanoguiWindow->setLayout(new nanogui::GroupLayout);

	nanogui::Button *nanoEasyButton = nanoguiWindow->add<nanogui::Button>("Easy");
	nanoEasyButton->setCallback([&] {
		this->_game->setDifficulty(1);
		this->_game->getSound().playMenuClick();
		newGameButton();
	});
	if (index == 1)
		nanoEasyButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));


	nanogui::Button *nanoMediumButton = nanoguiWindow->add<nanogui::Button>("Medium");
	nanoMediumButton->setCallback([&] {
		this->_game->setDifficulty(1);
		this->_game->getSound().playMenuClick();
		newGameButton();
	});
	if (index == 2)
		nanoMediumButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	nanogui::Button *nanoHardButton = nanoguiWindow->add<nanogui::Button>("Hard");
	nanoHardButton->setCallback([&] {
		this->_game->setDifficulty(1);
		this->_game->getSound().playMenuClick();
		newGameButton();
	});
	if (index == 3)
		nanoHardButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	new nanogui::Label(nanoguiWindow, "");
	new nanogui::Label(nanoguiWindow, "");
	nanogui::Button *nanoExitButton = nanoguiWindow->add<nanogui::Button>("Back");
	nanoExitButton->setCallback([&] {
		_menuState = MenuState::MAIN_MENU;
	});
	if (index == 4)
		nanoExitButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::DIFFICULTY && !breaker){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (getDelayTimer() >= 10) {
			if (checkMenuSelectionKeys() != 0) {
				index += checkMenuSelectionKeys();
				if (index > 4)
					index = 1;
				if (index < 1)
					index = 4;
				breaker = true;
				this->_game->getSound().playMenuKeypress();
			}

			if (glfwGetKey(*_win, GLFW_KEY_ENTER))
				switch (index) {
					case 1 :
						this->_game->setDifficulty(1);
						newGameButton();
						break;
					case 2 :
						this->_game->setDifficulty(2);
						newGameButton();
						break;
					case 3 :
						this->_game->setDifficulty(3);
						newGameButton();
						break;
					case 4 :
						_menuState = MenuState::MAIN_MENU;
						break;
				}
			else if (this->_game->getKeyPressArr(ESCAPE)) {
				_menuState = MenuState::MAIN_MENU;
				_game->getSound().playMenuClick();
			}
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(*_win))
		exitButton();
	nanoguiWindow->dispose();
}

void			Menu::levelFailMenu() {
	nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), "Failure");
	static int 			index = 1;
	bool 				breaker = false;

	nanoguiWindow->setLayout(new nanogui::GroupLayout);

	new nanogui::Label(nanoguiWindow, "You Died.");

	nanogui::Button *nanoExitButton = nanoguiWindow->add<nanogui::Button>("Back");
	nanoExitButton->setCallback([&] {
		_game->getSound().playMenuClick();
		_menuState = MenuState::MAIN_MENU;
		this->_game->setGameState(GameState::MENU);
	});
	if (index == 1)
		nanoExitButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	nanogui::Button *nanoTryAgainButton = nanoguiWindow->add<nanogui::Button>("Try Again");
	nanoTryAgainButton->setCallback([&] {
		newGameButton();
	});
	if (index == 2)
		nanoTryAgainButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));


	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::LEVEL_FAIL && !breaker){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (getDelayTimer() >= 10) {
			if (checkMenuSelectionKeys() != 0) {
				index += checkMenuSelectionKeys();
				if (index == 1)
					index = 2;
				else
					index = 1;
				breaker = true;
				this->_game->getSound().playMenuKeypress();
			}

			if (glfwGetKey(*_win, GLFW_KEY_ENTER))
				switch (index) {
					case 1 :
						_menuState = MenuState::MAIN_MENU;
						this->_game->setGameState(GameState::MENU);
						_game->getSound().playMenuClick();
						break;
					case 2 :
						newGameButton();
						_game->getSound().playMenuClick();
						break;
				}
			else if (this->_game->getKeyPressArr(ESCAPE)) {
				_menuState = MenuState::MAIN_MENU;
				_game->getSound().playMenuClick();
			}
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(*_win))
		exitButton();
	nanoguiWindow->dispose();
}

void			Menu::levelPassMenu() {
	nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(400, 800), "Success");
	static int 			index = 1;
	bool 				breaker = false;

	nanoguiWindow->setLayout(new nanogui::GroupLayout);

	new nanogui::Label(nanoguiWindow, "Congratulations!");

	nanogui::Button *nanoExitButton = nanoguiWindow->add<nanogui::Button>("Back to menu");
	nanoExitButton->setCallback([&] {
		_game->getSound().playMenuClick();
		_menuState = MenuState::MAIN_MENU;
		this->_game->setGameState(GameState::MENU);
	});
	if (index == 1)
		nanoExitButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	nanogui::Button *nanoTryAgainButton = nanoguiWindow->add<nanogui::Button>("Try Again");
	nanoTryAgainButton->setCallback([&] {
		newGameButton();
	});
	if (index == 2)
		nanoTryAgainButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	nanogui::Button *nanoNextLevelButton = nanoguiWindow->add<nanogui::Button>("Next Level");
	nanoNextLevelButton->setCallback([&] {
		//add in a next level thing
		newGameButton();
	});
	if (index == 3)
		nanoNextLevelButton->setBackgroundColor(Eigen::Vector4i(105, 105, 105, 255));

	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->center();
	resetDelayTimer();
	while (!glfwWindowShouldClose(*_win) && _menuState == MenuState::LEVEL_FAIL && !breaker){
		glfwPollEvents();
		updateKeys();
		updateMouse();
		if (getDelayTimer() >= 10) {
			if (checkMenuSelectionKeys() != 0) {
				index += checkMenuSelectionKeys();
				if (index > 4)
					index = 1;
				if (index < 1)
					index = 4;
				breaker = true;
				this->_game->getSound().playMenuKeypress();
			}
			if (glfwGetKey(*_win, GLFW_KEY_ENTER))
				switch (index) {
					case 1 :
						_menuState = MenuState::MAIN_MENU;
						this->_game->setGameState(GameState::MENU);
						_game->getSound().playMenuClick();
						break;
					case 2 :
						newGameButton();
						_game->getSound().playMenuClick();
						break;
					case 3 :
						newGameButton();
						break;

				}
			else if (this->_game->getKeyPressArr(ESCAPE)) {
				_menuState = MenuState::MAIN_MENU;
				_game->getSound().playMenuClick();
			}
		}
		renderMenu();
	}
	if (glfwWindowShouldClose(*_win))
		exitButton();
	nanoguiWindow->dispose();
}

void			Menu::updateKeys() {
	if (glfwGetKey(*_win, this->_game->getSettings().getUpKey()) == GLFW_PRESS)
		this->_game->setKeyPressArr(UP, true);
	else
		this->_game->setKeyPressArr(UP, false);

	if (glfwGetKey(*_win, this->_game->getSettings().getDownKey()) == GLFW_PRESS)
		this->_game->setKeyPressArr(DOWN, true);
	else
		this->_game->setKeyPressArr(DOWN, false);

	if (glfwGetKey(*_win, this->_game->getSettings().getLeftKey()) == GLFW_PRESS)
		this->_game->setKeyPressArr(LEFT, true);
	else
		this->_game->setKeyPressArr(LEFT, false);

	if (glfwGetKey(*_win, this->_game->getSettings().getRightKey()) == GLFW_PRESS)
		this->_game->setKeyPressArr(RIGHT, true);
	else
		this->_game->setKeyPressArr(RIGHT, false);

	if (glfwGetKey(*_win, this->_game->getSettings().getActionKey()) == GLFW_PRESS)
		this->_game->setKeyPressArr(ACTION, true);
	else
		this->_game->setKeyPressArr(ACTION, false);

	if (glfwGetKey(*_win, this->_game->getSettings().getAcceptKey()) == GLFW_PRESS)
		this->_game->setKeyPressArr(ACCEPT, true);
	else
		this->_game->setKeyPressArr(ACCEPT, false);

	if (glfwGetKey(*_win, this->_game->getSettings().getEscapeKey()) == GLFW_PRESS)
		this->_game->setKeyPressArr(ESCAPE, true);
	else
		this->_game->setKeyPressArr(ESCAPE, false);
}

void			Menu::updateMouse() {
	int				state;
	static bool		wasClicked = false;
	static double	clickX;
	static double	clickY;

	glfwGetCursorPos(*_win, &_mouseX, &_mouseY);
	state = glfwGetMouseButton(*_win, GLFW_MOUSE_BUTTON_1);
	if (state == GLFW_PRESS && wasClicked == false) {
		//std::cout << "clicked at:   " << _mouseX << ",  " << _mouseY << std::endl;
		wasClicked = true;
		clickX = _mouseX;
		clickY = _mouseY;
	}
	else if (state == GLFW_RELEASE && wasClicked) {
		//std::cout << "released at:  " << _mouseX << ",  " << _mouseY << std::endl;
		wasClicked = false;
	}
}

bool            Menu::checkPlayerNameAvailability(std::string playerNameInputVar) {
	std::vector<std::string> 			playerNames = this->_game->checkPlayers();

	if (playerNames.size() > 0) {
		for (std::vector<std::string>::iterator it = playerNames.begin(); it != playerNames.end(); ++it) {
			if (iequals(*it, playerNameInputVar)) {
				std::cout << "New name was found: " << playerNameInputVar << " Found: " << *it << std::endl;
				return (false);
			}
		}
	}
	return (true);
}

bool 			Menu::iequals(const std::string& a, const std::string& b) {
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
	if (playerNameInputVar == "Enter your name")
		errorPopup("ERROR!", "You cannot have that name.", "OK");
	else if (checkPlayerNameAvailability(playerNameInputVar)) {
		this->_game->setPlayer(Player(playerNameInputVar));
		this->_game->savePlayer();
		_menuState = MenuState::MAIN_MENU;
		std::cout << "Player : " << playerNameInputVar << " created" << std::endl;
		_game->getSound().playMenuClick();
	}
	else
		errorPopup("ERROR!", "Name already in use.", "OK");
}

void 			Menu::selectButton(std::vector<std::string> playerNames, int nameIndex) {
	if (playerNames[nameIndex] != "") {
		this->_game->loadPlayer(playerNames[nameIndex]);
		_game->getSound().playMenuClick();
	}
	if (this->_game->getSettings().getWindowed())
		glfwSetWindowMonitor(*(_win), NULL, this->_game->getSettings().getXPos(), this->_game->getSettings().getYPos(), this->_game->getSettings().getResolutionX(), this->_game->getSettings().getResolutionY(), GLFW_DONT_CARE);
	else
		glfwSetWindowMonitor(*(_win), glfwGetPrimaryMonitor(), 0, 0, this->_game->getSettings().getResolutionX(), this->_game->getSettings().getResolutionY(), GLFW_DONT_CARE);
	_menuState = MenuState::MAIN_MENU;
}

void			Menu::deleteButton(std::vector<std::string> playerNames, int nameIndex) {
	std::string fileName = "resources/profiles/" + playerNames[nameIndex] + ".profile";
	std::cout <<"Attempting removal of profile:" << fileName << std::endl;
	if (remove(fileName.c_str()) != 0)
		std::cerr << "Error: Could not delete file: " << fileName << std::endl;
	else {
		std::cout << "Deleted profile: " << fileName << std::endl;
		_game->getSound().playMenuClick();
	}
}

void			Menu::exitButton() {
	this->_game->setGameState(GameState::EXIT);
	_menuState = MenuState::NO_MENU;
}

void            Menu::newGameButton() {
	std::cout << "New Game pressed." << std::endl;
	this->_game->setGameState(GameState::PLAY);
	this->_game->setPlayState(PlayState::GAME_INIT);
	_menuState = MenuState::NO_MENU;
	_game->getSound().playMenuClick();
}

void            Menu::loadGameButton() {
	std::cout << "HAS SAVES" << std::endl;
	_game->getSound().playMenuClick();
}

void            Menu::playerSelectButton() {
	std::cout << "Change Player pressed." << std::endl;
	_menuState = MenuState::PLAYER_SELECT;
}

void            Menu::settingsButton() {
	std::cout << "Settings pressed." << std::endl;
	_menuState = MenuState::SETTINGS;
	_game->getSound().playMenuClick();
}

void            Menu::logoutButton() {
	std::cout << "Logout pressed." << std::endl;
	_game->getSound().playMenuClick();
	_menuState = MenuState::PLAYER_SELECT;
	this->_game->setPlayer(Player());
	this->_game->setSettings(Settings());
	glfwSetWindowMonitor(*(_win), NULL, this->_game->getSettings().getXPos(), this->_game->getSettings().getYPos(), this->_game->getSettings().getResolutionX(), this->_game->getSettings().getResolutionY(), GLFW_DONT_CARE);
}

void			Menu::applyButton(int selectedIndex, Settings *tempSettings) {
	switch (selectedIndex) {
		case 0 :
			tempSettings->setResolution(std::make_pair(800, 600));
			break;
		case 1 :
			tempSettings->setResolution(std::make_pair(1280, 800));
			break;
		case 2 :
			tempSettings->setResolution(std::make_pair(1920, 1080));
			break;
	}
	this->_game->setSettings(*tempSettings);
	std::cout << "Changes applied" << std::endl;
	this->_game->savePlayer();
	std::cout << "Player Saved" << std::endl;
	if (this->_game->getSettings().getWindowed())
		glfwSetWindowMonitor(*(_win), NULL, this->_game->getSettings().getXPos(), this->_game->getSettings().getYPos(), this->_game->getSettings().getResolutionX(), this->_game->getSettings().getResolutionY(), GLFW_DONT_CARE);
	else
		glfwSetWindowMonitor(*(_win), glfwGetPrimaryMonitor(), 0, 0, this->_game->getSettings().getResolutionX(), this->_game->getSettings().getResolutionY(), GLFW_DONT_CARE);
	if (this->_game->getPlayState() == PlayState::GAME_PLAY) {
		std::cout << "accepted changes 1" << std::endl;
		_menuState = MenuState::PAUSE;
	}
	else {
		std::cout << "accepted changes 2" << std::endl;
		quitToMenuButton();
	}
}

void            Menu::keyBindingButton() {
	std::cout << "keybinding menu" << std::endl;
	_menuState = MenuState::KEYBINDING;
}

void            Menu::resumeButton() {
	this->_game->getSound().playMenuClick();
	this->_game->setGameState(GameState::PLAY);
	_menuState = MenuState::NO_MENU;
}

void            Menu::quitToMenuButton() {
	this->_game->getSound().playMenuClick();
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