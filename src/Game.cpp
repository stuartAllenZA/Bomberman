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

void					Game::loadStuff() {

}