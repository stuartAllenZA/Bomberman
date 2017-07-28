#include <Game.hpp>

Game::Game() : _exit(false), _gameInput(0) {
	this->_settings = new Settings();
	this->_player = new Player();
	std::cout << "Game Constructed\n";
}

Game::Game(Game const & src) {
	*this = src;
	std::cout << "Game Copy-Constructed\n";
}

Game::~Game() {
	std::cout << "Game De-Constructed\n";
}

Game &		Game::operator=(Game const & src) {
	this->_exit = src.getExit();
	this->_gameInput = src.getGameInput();
	return (*this);
}

bool		Game::getExit() const {
	return (this->_exit);
}

void		Game::setExit(const bool newExit) {
	this->_exit = newExit;
}

int			Game::getGameInput() const {
	return (this->_gameInput);
}

void		Game::setGameInput(const int newInput) {
	this->_gameInput = newInput;
}

void		Game::loadStuff() {

}