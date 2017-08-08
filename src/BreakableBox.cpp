#include <BreakableBox.hpp>

BreakableBox::BreakableBox() {
	std::cout << "BreakableBox at " << xy << " Constructed\n";
}

BreakableBox::BreakableBox(BreakableBox const & src) {
	std::cout << "BreakableBox Copy-Constructed\n";
	*this = src;
}

BreakableBox::~BreakableBox() {
	std::cout << "BreakableBox De-Constructed\n";
}

BreakableBox &			BreakableBox::operator=(BreakableBox const & src) {
	this->_xy = src.getXY();
	this->_drop = src.getDrop();
	return (*this);
}

std::pair<int, int>	BreakableBox::getXY() const {
	return (this->_xy);
}

void				BreakableBox::setXY(const std::pair<int, int> xy) {
	this->_xy = xy;
}

Drop 				BreakableBox::getDrop() const {
	return (this->_drop);
}

void				BreakableBox::setDrop(const Drop *newDrop) {
	this->_drop = newDrop;
}
