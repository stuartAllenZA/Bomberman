#include <Player.hpp>

Player::Player(std::pair<int, int> xy, int lives, std::string name) : Character(xy, lives), _name(name), _level(1), _experience(0) {
	this->_fileLocation = "resources/profiles/" + name + ".player";
	std::cout << "Player with name" << this->_name << ", XY & Lives Constructed\n";
}

Player::Player(std::pair<int, int> xy, std::string name) : Character(xy), _name(name), _level(1), _experience(0) {
	this->_fileLocation = "resources/profiles/" + name + ".player";
	std::cout << "Player with name" << this->_name << "& XY Constructed\n";
}

Player::Player(int lives, std::string name) : Character(lives), _name(name), _level(1), _experience(0) {
	this->_fileLocation = "resources/profiles/" + name + ".player";
	std::cout << "Player with name" << this->_name << " & Lives Constructed\n";
}

Player::Player(std::string name) : Character(), _name(name), _level(1), _experience(0) {
	this->_fileLocation = "resources/profiles/" + name + ".player";
	std::cout << "Player with name" << this->_name << " Default Constructed\n";
}

Player::Player(Player const & src) {
	std::cout << "Player with name" << this->_name << " Copy-Constructed\n";
	*this = src;
}

Player::~Player() {
	std::cout << "Player with name" << this->_name << " De-Constructed\n";
}

Player &	Player::operator=(Player const & src) {
	this->_fileLocation = src.getFileLocation();
	this->_name = src.getName();
	this->_level = src.getLevel();
	this->_experience = src.getExperience();
	return (*this);
}

std::string	Player::getFileLocation() const {
	return (this->_fileLocation);
}

void		Player::setFileLocation(const std::string newLocation) {
	this->_fileLocation = newLocation;
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
