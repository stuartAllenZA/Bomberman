#include <Game.hpp>

Game::Game() : _state(GameState::MENU), _gameInput(0) {
	std::cout << "Constructing Game\n";
	this->_settings = Settings();
	if (!this->_settings.getLastPlayer().empty())
	{
		this->_player = new Player(this->_settings.getLastPlayer());
		loadPlayer(this->_settings.getLastPlayer());
	}
	std::cout << "Game Constructed\n";
}

Game::Game(Game const & src) {
	*this = src;
	std::cout << "Game Copy-Constructed\n";
}

Game::~Game() {
	std::cout << "De-Constructing Game\n";
	//delete this->_player; THIS LINE CAUSES BUS ERRORS OCCASIONALLY
	std::cout << "Game De-Constructed\n";
}

Game &					Game::operator=(Game const & src) {
	this->_state = src.getState();
	this->_gameInput = src.getGameInput();
	return (*this);
}

GameState				Game::getState() const {
	return (this->_state);
}

void					Game::setState(const GameState newState) {
	this->_state = newState;
}

int						Game::getGameInput() const {
	return (this->_gameInput);
}

void					Game::setGameInput(const int newInput) {
	this->_gameInput = newInput;
}

Settings				Game::getSettings() const {
	return (this->_settings);
}

void					Game::setSettings(const Settings newSettings) {
	this->_settings = newSettings;
}

Player*				Game::getPlayer() const {
	return (this->_player);
}

void					Game::setPlayer(Player *newPlayer) {
	this->_player = newPlayer;
}

std::vector<Character*>	Game::getEnemies() const {
	return (this->_enemies);
}

void					Game::setEnemies(const std::vector<Character*> newEnemies) {
	this->_enemies = newEnemies;
}

std::string				Game::newUser(std::string playerName) {
	DIR	*directory = opendir("resources/profiles/");
	struct dirent *contents;
	while ((contents = readdir(directory)) != NULL) {
		if (contents->d_name == playerName)
			return "user already exists";
	}
	savePlayer();
	closedir(directory);
	return "success message";
}

void					Game::saveSettings() {
	std::ofstream settingsOut("resources/bomberman.config", std::ofstream::out);
	settingsOut << "resolutionX:" + (std::to_string(this->_settings.getResolutionX()))+"\n";
	settingsOut << "resolutionY:" + (std::to_string(this->_settings.getResolutionY()))+"\n";
	if (this->_settings.getWindowed())
		settingsOut << "windowed:true\n";
	else
		settingsOut << "windowed:false\n";
	settingsOut << "upKey:" + (std::to_string(this->_settings.getUpKey()))+"\n";
	settingsOut << "downKey:" + (std::to_string(this->_settings.getDownKey()))+"\n";
	settingsOut << "leftKey:" + (std::to_string(this->_settings.getLeftKey()))+"\n";
	settingsOut << "rightKey:" + (std::to_string(this->_settings.getRightKey()))+"\n";
	settingsOut << "actionKey:" + (std::to_string(this->_settings.getActionKey()))+"\n";
	settingsOut << "musicVol:" + (std::to_string(this->_settings.getMusicVol()))+"\n";
	settingsOut << "FXVol:" + (std::to_string(this->_settings.getFXVol()))+"\n";
	settingsOut.close();
	std::cout << "Settings saved to ./resources/bomberman.config.\n";
}

void					Game::savePlayer() {
	std::ofstream profileFileOut("resources/profiles/" + this->_player->getName() + ".player", std::ofstream::out);
	profileFileOut << "level:" + (std::to_string(this->_player->getLevel()))+"\n";
	profileFileOut << "experience:" + (std::to_string(this->_player->getExperience()))+"\n";
	profileFileOut.close();
	std::cout << "Player saved to ./resources/profiles/" << this->_player->getName() << ".player\n";
}

void					Game::saveGame() {
	std::ofstream saveFileOut("resources/save/" + this->_player->getName() + ".save", std::ofstream::out);
	// insert save data here
	// e.g.	saveFileOut << "playerHP:"+(std::to_string(_player->getHP()))+"\n";
	saveFileOut.close();
	std::cout << "Game saved to ./resources/profiles/" << this->_player->getName() << ".save\n";
}

void					Game::loadPlayer(std::string playerName) {
	std::string fileName = "resources/profiles/" + playerName + ".profile";
	this->_player->setLevel(std::stoi(lexFile(fileName, "level")));
	this->_player->setExperience(std::stoi(lexFile(fileName, "experience")));
}

void					Game::loadGame() {
}

void					Game::loadSettings() {
	std::string fileName = "resources/bomberman.config";
	struct stat buffer;   
  	if (stat(fileName.c_str(), &buffer) == 0)
  		std::cout << "Cannot find file '" << fileName << "'. Using default settings.";
	int resX = std::stoi(lexFile(fileName, "resolutionX"));
	int resY = std::stoi(lexFile(fileName, "resolutionY"));
	std::pair<int, int> resolution = std::make_pair(resX, resY);
	this->_settings.setResolution(resolution);

	std::string ret = lexFile(fileName, "windowed");
	if (ret == "false")
		this->_settings.setWindowed(false);
	else
		this->_settings.setWindowed(true);

	this->_settings.setUpKey(std::stoi(lexFile(fileName, "upKey")));
	this->_settings.setDownKey(std::stoi(lexFile(fileName, "downKey")));
	this->_settings.setLeftKey(std::stoi(lexFile(fileName, "leftKey")));
	this->_settings.setRightKey(std::stoi(lexFile(fileName, "rightKey")));
	this->_settings.setActionKey(std::stoi(lexFile(fileName, "actionKey")));
	this->_settings.setMusicVol(std::stoi(lexFile(fileName, "musicVol")));
	this->_settings.setFXVol(std::stoi(lexFile(fileName, "FXVol")));
}

std::string				Game::lexFile(std::string fileName, std::string find) {
	std::ifstream handle(fileName);
	std::string line;
	std::string key;
	std::string value;
	int			num;

	num = 0;
	if (!handle)
		throw (Exceptions::LexOpenFileError(fileName));
	else
	{
		while (std::getline(handle, line)) {
			num++;
			if (!line.empty()) {
				std::istringstream	iss(line);
				if (line.c_str()[0] != ';' && line.c_str()[0] != '[')
				{
					if (iss >> key >> value) {
						if (key == find)
							return value;
					}
					else
						throw (Exceptions::LexFormatError(num, line));
				}
			}
		}
		throw (Exceptions::LexKeyNotFound(find));
	}		
	return ("ERROR");
}

std::ostream & 			operator<<(std::ostream & o, Game const & rhs) {
	int num = 0;
	o << "Dumping Game State\nGame State: " << static_cast<std::underlying_type<GameState>::type>(rhs.getState()) << "\nGame Input: " << rhs.getGameInput() << std::endl;
	if (rhs.getEnemies().size() > 0) {
		for (std::vector<Character*>::iterator it = rhs.getEnemies().begin(); it != rhs.getEnemies().end(); ++it)
		{
			num++;
			o << "Enemy " << num << ": " << *it << std::endl;
		}
	}
	else
		o << "Enemies: 0\n";
	o << rhs.getSettings() << std::endl;
	return o;
}

/*
void				Game::up() {
	// update coords x++;
}

void				Game::updateGameData() {
	switch (_gameInput) {
		case UP:
		case DOWN:
		case LEFT:
		case RIGHT:
		case SPACE:
		case ESC:
	}
	// detectCollisions
	// AIBehaveUpdate
	// detectCollisions
}

// map has to have an odd number of x's and y's
// i.e. maxX and maxY must be even numbers (starting at 0)
void				Game::mapGenerator(int xMax, int yMax) {
	for (int xmin = 0; xmin < xmax; xmin++) {
		for (int ymin = 0; ymin < ymax; ymin++) {
			if (xmin != 0 && ymin != 0 && xmin != xmax && ymin != ymax) {
				if (xmin % 2 == 0 && ymin % 2 == 0) {
					unbreakableWallTemp	unbreakableWall(xmin, ymin);
					_unbreakableWalls.push_back(*unbreakableWall);
				}
			}
			else if (xmin == 0 || xmin == xmax || ymin == 0 || ymin == ymax) {
				unbreakableWallTemp	unbreakableWall(xmin, ymin);
				_unbreakableWalls.push_back(*unbreakableWall);
			}
		}
	}
}
*/
