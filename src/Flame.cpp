#include <Flame.hpp>

Flame::Flame(std::pair<float, float> xy, std::uint64_t timeToDie) : _xy(xy), _timeToDie(timeToDie) {
	std::cout << "Flame at x: " << xy.first << " y: " << xy.second << " Constructed\n";
}

Flame::Flame(Flame const & src) {
	std::cout << "Flame Copy-Constructed\n";
	*this = src;
}

Flame::~Flame() {
	std::cout << "Flame De-Constructed\n";
}

Flame &			Flame::operator=(Flame const & src) {
	this->_xy = src.getXY();
	this->_timeToDie = src.getTimeToDie();
	return (*this);
}

std::pair<float, float>	Flame::getXY() const {
	return (this->_xy);
}

void				Flame::setXY(const std::pair<float, float> xy) {
	this->_xy = xy;
}

std::uint64_t		Flame::getTimeToDie() const {
	return (this->_timeToDie);
}

void				Flame::setTimeToDie(const std::uint64_t newTTD) {
	this->_timeToDie = newTTD;
}
