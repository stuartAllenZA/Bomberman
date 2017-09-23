#ifndef INCLUDE_BOX_CLASS_HPP_
#define INCLUDE_BOX_CLASS_HPP_

#include <iostream>
#include <Drop.hpp>

class Box {
public:
	Box();
	Box(Drop *drop);
	Box(std::pair<float, float> xy);
	Box(std::pair<float, float> xy, Drop *drop);
	virtual ~Box()=0;
	Box(Box const & src);
	Box	&					operator=(Box const &src);
	std::pair<float, float>	getXY() const;
	void					setXY(const std::pair<float, float> xy);
	Drop					*getDrop() const;
	void					setDrop(Drop *newDrop);

	void					placeRandomly();

protected:
	std::pair<float, float>	_xy;
	Drop					*_drop;
};

#endif

