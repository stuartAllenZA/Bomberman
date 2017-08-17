#ifndef INCLUDE_UNBREAKABLE_BOX_CLASS_HPP_
#define INCLUDE_UNBREAKABLE_BOX_CLASS_HPP_

#include "Box.hpp"
#include "Drops.hpp"

class UnbreakableBox : public Box {
public:
	UnbreakableBox();
	~UnbreakableBox();
	UnbreakableBox(UnbreakableBox const &src);
	UnbreakableBox		&operator=(UnbreakableBox const &src);std::pair<int, int>	getXY() const;
	void				setXY(const std::pair<int, int> xy);
	Drop				*getDrop();
	void				setDrop(const Drop *newDrop) const;

private:
	Drop					*_drop;
};

#endif

