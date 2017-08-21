#ifndef INCLUDE_EXTRA_BOMB_HPP_
#define INCLUDE_EXTRA_BOMB_HPP_

#include "Drop.hpp"

class ExtraBomb : public Drop {
	public:
		ExtraBomb(std::pair<int, int> xy);
		~ExtraBomb();
		ExtraBomb(ExtraBomb const & src);
		ExtraBomb	&operator=(ExtraBomb const &src);
	private:
};

#endif

