#include <UnbreakableBox.hpp>

UnbreakableBoxUnbreakableBox::UnbreakableBox() {
	std::cout << "UnbreakableBox at " << xy << " Constructed\n";
}

UnbreakableBox::UnbreakableBox(UnbreakableBox const & src) {
	std::cout << "UnbreakableBox Copy-Constructed\n";
	*this = src;
}

UnbreakableBox::~UnbreakableBox() {
	std::cout << "UnbreakableBox De-Constructed\n";
}

UnbreakableBox &	UnbreakableBox::operator=(UnbreakableBox const & src) {
	this->_xy = src.getXY();
	this->_drop = src.getDrop();
	return (*this);
}

std::pair<int, int>	UnbreakableBox::getXY() const {
	return (this->_xy);
}

void				UnbreakableBox::setXY(const std::pair<int, int> xy) {
	this->_xy = xy;
}

Drop 				UnbreakableBox::getDrop() const {
	return (this->_drop);
}

void				UnbreakableBox::setDrop(const Drop *newDrop) {
	this->_drop = newDrop;
}
