#ifndef INCLUDE_DROPS_CLASS_HPP_
#define INCLUDE_DROPS_CLASS_HPP_

#include "Bomb.hpp"

class Drop {
	public:
		virtual setSpawnPoint(...)=0
		virtual	getEffect(...)=0;
		virtual ~Drop()=0;
	private:
		std::pair<int, int>		_xy;
};

#endif

