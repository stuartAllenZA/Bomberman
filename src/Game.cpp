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

std::vector<Character>	Game::getEnemies() const {
	return (this->_enemies);
}

void					Game::setEnemies(const std::vector<Character> newEnemies) {
	this->_enemies = newEnemies;
}

std::string				Game::getUsername() {
	return _username;
}

void					Game::setUsername(std::string username) {
	_username = username;
	_profileFile = _username+".profile";
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
	// write save data to resources/saves/_username.save
}

void					Game::loadUserProfile() {
	// save data from resources/profiles/_username.profile into memory
}

void					Game::loadGame() {
	// save data from resources/saves/_username.save into memory
}

void					Game::loadSettings() {
	// save data from bomberman.config into memory
}

