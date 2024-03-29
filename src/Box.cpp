#include <Box.hpp>

Box::Box() : _drop(nullptr) {
	// std::cout << "Box Default Constructed\n";
}

Box::Box(Drop *drop) : _drop(drop) {
	// if (drop)
	// 	std::cout << "Box with drop Constructed\n";
	// else
	// 	std::cout << "Box was passed a NULL drop, Constructed\n";
}

Box::Box(std::pair<float, float> xy) : _xy(xy), _drop(nullptr) {
	// std::cout << "Box at x: " << xy.first << " y: " << xy.second << " Constructed\n";
}

Box::Box(std::pair<float, float> xy, Drop *drop) : _xy(xy), _drop(drop) {
	// if (drop)
	// 	std::cout << "Box with drop at x: " << xy.first << " y: " << xy.second << " Constructed\n";
	// else
	// 	std::cout << "Box at x: " << xy.first << " y: " << xy.second << " was passed a NULL drop, Constructed\n";
}

Box::Box(Box const & src) {
	// std::cout << "Box Copy-Constructed\n";
	*this = src;
}

Box::~Box() {
	// std::cout << "Box De-Constructed\n";
}

Box &					Box::operator=(Box const & src) {
	this->_xy = src.getXY();
	this->_drop = src.getDrop();
	return (*this);
}

std::pair<float, float>	Box::getXY() const {
	return (this->_xy);
}

void					Box::setXY(const std::pair<float, float> xy) {
	this->_xy = xy;
}

Drop					*Box::getDrop() const {
	return (this->_drop);
}

void					Box::setDrop(Drop *newDrop) {
	if (this->_drop)
		delete this->_drop;
	this->_drop = newDrop;
}

void					Box::placeRandomly() {
	//Generate numbers within Max X & Y
	//Check to see if that position on map is free
	//If so, assign numbers to _xy
	//If not, re-generate numbers
}