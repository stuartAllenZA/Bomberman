#include <Character.hpp>

Character::Character(std::pair<float, float> xy, int speed, int health, int lives, char ori) : _xy(xy), _speed(speed), _health(health), _lives(lives), _ori(ori), _size(0.0) {
	//std::cout << "Character with XY, Speed, Health & Lives Constructed\n";
}

Character::Character(std::pair<float, float> xy, int speed, int health, int lives) : _xy(xy), _speed(speed), _health(health), _lives(lives), _ori('E'), _size(0.0) {
	//std::cout << "Character with XY, Speed, Health & Lives Constructed\n";
}

Character::Character(std::pair<float, float> xy, int speed, int health, char ori) : _xy(xy), _speed(speed), _health(health), _lives(1), _ori(ori), _size(0.0) {
	//std::cout << "Character with XY, Speed & Health Constructed\n";
}

Character::Character(std::pair<float, float> xy, int speed, int health) : _xy(xy), _speed(speed), _health(health), _lives(1), _ori('E'), _size(0.0) {
	//std::cout << "Character with XY, Speed & Health Constructed\n";
}

Character::Character(std::pair<float, float> xy, int lives) : _xy(xy), _speed(100), _health(100), _lives(lives), _ori('E'), _size(0.0) {
	//std::cout << "Character with XY & Lives Constructed\n";
}

Character::Character(std::pair<float, float> xy) : _xy(xy), _speed(100), _health(100), _lives(1), _ori('E'), _size(0.0) {
	//std::cout << "Character with XY Constructed\n";
}

Character::Character(int lives) : _xy(std::make_pair(0.0, 0.0)), _speed(100), _health(100), _lives(lives), _ori('E'), _size(0.0) {
	//std::cout << "Character with Lives Constructed\n";
}

Character::Character() : _xy(std::make_pair(0.0, 0.0)), _speed(100), _health(100), _lives(1), _ori('E'), _size(0.0) {
	//std::cout << "Character Default Constructed\n";
}

Character::Character(Character const & src) {
	//std::cout << "Character Copy-Constructed\n";
	*this = src;
}

Character::~Character() {
	//std::cout << "Character De-Constructed\n";
}

Character &			Character::operator=(Character const & src) {
	this->_xy = src.getXY();
	this->_speed = src.getSpeed();
	this->_health = src.getHealth();
	this->_lives = src.getLives();
	this->_ori = src.getOri();
	this->_size = src.getSize();
	return (*this);
}

std::pair<float, float>	Character::getXY() const {
	return (this->_xy);
}

void				Character::setXY(const std::pair<float, float> xy) {
	this->_xy = xy;
}

int 				Character::getSpeed() const {
	return (this->_speed);
}

void				Character::setSpeed(const int newSpeed) {
	this->_speed = newSpeed;
}

int 				Character::getHealth() const {
	return (this->_health);
}

void				Character::setHealth(const int newHealth) {
	this->_health = newHealth;
}

int 				Character::getLives() const {
	return (this->_lives);
}

void				Character::setLives(const int newLives) {
	this->_lives = newLives;
}

char				Character::getOri() const {
	return (this->_ori);
}

void				Character::setOri(const char newOri) {
	this->_ori = newOri;
}

float				Character::getSize() const {
	return (this->_size);
}

void				Character::setSize(const float newSize) {
	this->_size = newSize;
}