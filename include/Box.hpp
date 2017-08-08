#ifndef INCLUDE_BOX_CLASS_HPP_
#define INCLUDE_BOX_CLASS_HPP_

#include <iostream>

class IBox {
public:
	virtual ~Box() {}

protected:
	std::pair<int, int>		_xy;
};

#endif
