#ifndef INCLUDE_LEVEL_HATCH_HPP_
#define INCLUDE_LEVEL_HATCH_HPP_

#include "Drop.hpp"

class LevelHatch : public : Drop {
	public:
		LevelHatch();
		~LevelHatch();
		LevelHatch(LevelHatch const & src);
		LevelHatch	&operator=(LevelHatch const &src);
	private:
};

#endif

