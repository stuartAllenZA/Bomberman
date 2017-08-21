#ifndef DROP_HPP
#define DROP_HPP

#include <iostream>

class Drop {
public:
	Drop();
	Drop(std::pair<int, int> xy);
	virtual ~Drop()=0;
	Drop(Drop const & src);
	Drop	&			operator=(Drop const &src);
	std::pair<int, int>	getXY() const;
	void				setXY(const std::pair<int, int> xy);

protected:
	std::pair<int, int>		_xy;
};

#endif

