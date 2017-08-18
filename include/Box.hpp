#ifndef INCLUDE_BOX_CLASS_HPP_
#define INCLUDE_BOX_CLASS_HPP_

#include <iostream>

class Box {
public:
	Box();
	Box(Drop *drop);
	Box(std::pair<int, int> xy);
	Box(std::pair<int, int> xy, Drop *drop);
	virtual ~Box()=0;
	Box(Box const & src);
	Box	&				operator=(Box const &src);
	std::pair<int, int>	getXY() const;
	void				setXY(const std::pair<int, int> xy);
	Drop				*getDrop() const;
	void				setDrop(const Drop *newDrop);

	void				placeRandomly();

protected:
	std::pair<int, int>		_xy;
	Drop					*_drop;
};

#endif

