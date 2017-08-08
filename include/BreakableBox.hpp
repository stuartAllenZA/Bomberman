#ifndef INCLUDE_BREAKABLE_BOX_CLASS_HPP_
#define INCLUDE_BREAKABLE_BOX_CLASS_HPP_

#include "Drops.hpp"

class BreakableBox : public Box {
public:
	BreakableBox(std::pair<int, int> xy;);
	~BreakableBox();
	BreakableBox(BreakableBox const &src);
	BreakableBox		&operator=(BreakableBox const &src);
	std::pair<int, int>	getXY() const;
	void				setXY(const std::pair<int, int> xy);
	Drop				*getDrop();
	void				setDrop(const Drop *newDrop) const;

private:
	Drop					*_drop;
};

#endif

