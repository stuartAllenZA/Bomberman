#include <Settings.hpp>

Settings::Settings() : _resolution(std::make_pair(800, 600)), _windowed(false), _upKey(119), _downKey(115), _leftKey(97), rightKey(100), _musicVol(100), _FXVol(100) {
	std::cout << "Settings Default Constructed\n";
}

Settings::Settings(Settings const & src) {
	std::cout << "Settings Copy-Constructed\n";
	*this = src;
}

Settings::~Settings() {
	std::cout << "Settings De-Constructed\n";
}

Settings &			Settings::operator=(Settings const & src) {
	this->_resolution = src.getXY();
	this->_windowed = src.getSpeed();
	this->_upKey = src.getHealth();
	this->_downKey = src.getLives();
	this->_leftKey = src.getLives();
	this->_rightKey = src.getLives();
	this->_musicVol = src.getLives();
	this->_FXVol = src.getLives();
	return (*this);
}

std::pair<int, int>	Settings::getResolution() const {
	return (this->_resolution);
}

void				Settings::setResolution(const std::pair<int, int> wh) {
	this->_resolution = wh;
}

bool				Settings::getWindowded() const {
	return (this->_windowed);
}

void				Settings::setWindowded(const bool newWin) {
	this->_windowed = newWin;
}

int 				Settings::getUpKey() const {
	return (this->_upKey);
}

void				Settings::setUpKey(const int newKey) {
	this->_upKey = newKey;
}

int 				Settings::getDownKey() const {
	return (this->_downKey);
}

void				Settings::setDownKey(const int newKey) {
	this->_downKey = newKey;
}

int 				Settings::getLeftKey() const {
	return (this->_leftKey);
}

void				Settings::setLeftKey(const int newKey) {
	this->_leftKey = newKey;
}

int 				Settings::getRightKey() const {
	return (this->_rightKey);
}

void				Settings::setRightKey(const int newKey) {
	this->_rightKey = newKey;
}

int 				Settings::getMusicVol() const {
	return (this->_musicVol);
}

void				Settings::setMusicVol(const int newVol) {
	this->_musicVol = newVol;
}

int 				Settings::getFXVol() const {
	return (this->_FXVol);
}

void				Settings::setUpKey(const int newVol) {
	this->_FXVol = newVol;
}