#include <Bomb.hpp>

Bomb::Bomb(std::pair<int, int> xy, int blastRange, int timeToDetonate, int numberCanLaunch, bool canBeRemoteDetonated) : _xy(xy), _blastRange(blastRange), _timeToDetonate(timeToDetonate), _numberCanLaunch(numberCanLaunch), _canBeRemoteDetonated(canBeRemoteDetonated) {
	std::cout << "Bomb at x: " << xy.first << " y: " << xy.second << " Constructed\n";
}

Bomb::Bomb(Bomb const & src) {
	std::cout << "Bomb Copy-Constructed\n";
	*this = src;
}

Bomb::~Bomb() {
	std::cout << "Bomb De-Constructed\n";
}

Bomb &			Bomb::operator=(Bomb const & src) {
	this->_xy = src.getXY();
	this->_blastRange = src.getBlastRange();
	this->_timeToDetonate = src.getTimeToDetonate();
	this->_numberCanLaunch = src.getNumberCanLaunch();
	this->_canBeRemoteDetonated = src.getCanBeRemoteDetonated();
	return (*this);
}

std::pair<int, int>	Bomb::getXY() const {
	return (this->_xy);
}

void				Bomb::setXY(const std::pair<int, int> xy) {
	this->_xy = xy;
}

int 				Bomb::getBlastRange() const {
	return (this->_blastRange);
}

void				Bomb::setBlastRange(const int newBlastRange) {
	this->_blastRange = newBlastRange;
}

int 				Bomb::getTimeToDetonate() const {
	return (this->_timeToDetonate);
}

void				Bomb::setTimeToDetonate(const int newTTD) {
	this->_timeToDetonate = newTTD;
}

int 				Bomb::getNumberCanLaunch() const {
	return (this->_numberCanLaunch);
}

void				Bomb::setNumberCanLaunch(const int newNCL) {
	this->_numberCanLaunch = newNCL;
}

bool				Bomb::getCanBeRemoteDetonated() const {
	return (this->_canBeRemoteDetonated);
}

void				Bomb::setCanBeRemoteDetonated(const bool newCBRD) {
	this->_canBeRemoteDetonated = newCBRD;
}