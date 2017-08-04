#ifndef INCLUDE_RANGE_EXTENDER_CLASS_HPP_
#define INCLUDE_RANGE_EXTENDER_CLASS_HPP_

#include "Drops.hpp"

class RangeExtender : public Drop {
	public:
		RangeExtender();
		~RangeExtender();
		RangeExtender(RangeExtender const & src);
		RangeExtender	&operator=(RangeExtender const &src);
	private:
};

#endif

