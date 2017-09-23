#ifndef DROP_HPP
#define DROP_HPP

#include <iostream>

class Drop {
public:
	Drop();
	Drop(std::pair<float, float> xy);
	virtual ~Drop()=0;
	Drop(Drop const & src);
	Drop	&			operator=(Drop const &src);
	std::pair<float, float>	getXY() const;
	void				setXY(const std::pair<float, float> xy);

protected:
	std::pair<float, float>		_xy;
};

#endif

