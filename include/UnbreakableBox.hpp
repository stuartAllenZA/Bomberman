#ifndef INCLUDE_UNBREAKABLE_BOX_CLASS_HPP_
#define INCLUDE_UNBREAKABLE_BOX_CLASS_HPP_

#include "Box.hpp"

class UnbreakableBox : public Box {
	public:
		UnbreakableBox();
		~UnbreakableBox();
		UnbreakableBox(UnbreakableBox const &src);
		UnbreakableBox		&operator=(UnbreakableBox const &src);
	private:
};

#endif

