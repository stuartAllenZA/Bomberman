#ifndef INCLUDE_BREAKABLE_BOX_CLASS_HPP_
#define INCLUDE_BREAKABLE_BOX_CLASS_HPP_

#include "Drops.hpp"

class BreakableBox : public Box {
	public:
		BreakableBox();
		~BreakableBox();
		BreakableBox(BreakableBox const &src);
		BreakableBox			&operator=(BreakableBox const &src);

		void					setHasDrop(bool hasDrop);;
		void					setDrop(Drop const &drop) const;

		bool					getHasDrop();
		Drop					*getDrop();

	private:
		bool					_hasDrop;
		Drop					*_drop;
};

#endif

