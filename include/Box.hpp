#ifndef INCLUDE_BOX_CLASS_HPP_
#define INCLUDE_BOX_CLASS_HPP_

#include <iostream>

class Box {
public:
	virtual ~Box() {}

protected:
	std::pair<int, int>		_xy;
};

#endif