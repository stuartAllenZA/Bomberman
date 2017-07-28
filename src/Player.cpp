#include <Player.hpp>

Player::Player(std::string name) : _name(name), _level(1), _experience(0) {
	std::cout << "Player with name" << name << " Default Constructed\n";
}

Player::Player(Player const & src) {
	std::cout << "Player with name" << name << " Copy-Constructed\n";
	*this = src;
}

Player::~Player() {
	std::cout << "Player with name" << name << " De-Constructed\n";
}

Player &			Player::operator=(Player const & src) {
	this->_name = src.getXY();
	this->_level = src.getSpeed();
	this->_experience = src.getHealth();
	return (*this);
}

std::string	Player::getName() const {
	return (this->_name);
}

void		Player::setName(const std::string newName) {
	this->_name = newName;
}

int 		Player::getLevel() const {
	return (this->_level);
}

void		Player::setLevel(const int newLevel) {
	this->_level = newLevel;
}

int 		Player::getExperience() const {
	return (this->_experience);
}

void		Player::setExperience(const int newExp) {
	this->_experience = newExp;
}
