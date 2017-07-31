#include <Game.hpp>

Game::Game() : _exit(false), _gameInput(0) {
	this->_settings = Settings();
	std::cout << "Game Constructed\n";
}

Game::Game(Game const & src) {
	*this = src;
	std::cout << "Game Copy-Constructed\n";
}

Game::~Game() {
	std::cout << "Game De-Constructed\n";
}

Game &					Game::operator=(Game const & src) {
	this->_exit = src.getExit();
	this->_gameInput = src.getGameInput();
	return (*this);
}

bool					Game::getExit() const {
	return (this->_exit);
}

void					Game::setExit(const bool newExit) {
	this->_exit = newExit;
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

Character				Game::getPlayer() const {
	return (this->_player);
}

void					Game::setPlayer(const Player newPlayer) {
	this->_player = newPlayer;
}

std::vector<Character>	Game::getEnemies() const {
	return (this->_enemies);
}

void					Game::setEnemies(const std::vector<Character> newEnemies) {
	this->_enemies = newEnemies;
}

int						Game::getCurrentLevel() {
	return _currentLevel;
}

int						Game::getCurrentExp() {
	return _currentExp;
}

void					Game::setCurrentLevel(int level) {
	_currentLevel = level;
}

void					Game::setCurrentExp(int exp) {
	_currentExp = exp;
}

std::string				Game::getUsername() {
	return _username;
}

void					Game::setUsername(std::string username) {
	_username = username;
	_profileFile = _username+".profile";
	_saveFile = _username+".save";
}

std::string				Game::newUser() {
	DIR	*directory = opendir("resources/profiles/");
	struct dirent *contents;
	while ((contents = readdir(directory)) != NULL) {
		if (contents->d_name == _profileFile)
			return "user already exists";
	}
	saveProfile();
	closedir(directory);
	return "success message";
}

void					Game::saveProfile() {
	std::ofstream profileFileOut("resources/profiles/"+_profileFile, std::ofstream::out);
	profileFileOut << "currentLevel:"+(std::to_string(_currentLevel))+"\n";
	profileFileOut << "exp:"+(std::to_string(_currentExp))+"\n";
	profileFileOut.close();
}

void					Game::saveGame() {
	std::ofstream saveFileOut("resources/save/"+_saveFile, std::ofstream::out);
	// insert save data here
	// e.g.	saveFileOut << "playerHP:"+(std::to_string(_player->getHP()))+"\n";
	saveFileOut.close();
}

void					Game::loadUserProfile() {
	std::ifstream handle("resources/profiles/"+_profileFile);
	std::string line;
	std::string key;
	std::string value;
	
	while (std::getline(handle, line)) {
		std::istringstream	iss(line);
		if (iss >> key >> value) {
			if (key == "currentLevel")
				_currentLevel = std::stoi(value);
			else if (key == "exp")
				_currentExp = std::stoi(value);
			// etc ...
		}
	}
}

void					Game::loadGame() {
	std::ifstream handle("resources/saves/"+_saveFile);
	std::string line;
	std::string key;
	std::string value;
	
	while (std::getline(handle, line)) {
		std::istringstream	iss(line);
		if (iss >> key >> value) {
			if (key == "playerHP")
				_player.setHealth(std::stoi(value));
			// etc ...
		}
	}
}

void					Game::loadSettings() {
	std::ifstream handle("bomberman.config");
	std::string line;
	std::string key;
	std::string value;
	
	while (std::getline(handle, line)) {
		std::istringstream	iss(line);
		if (iss >> key >> value) {
			if (key == "windowRes")
				_settings.setWindowded(std::stoi(value));
			// etc ...
		}
	}
}

