#ifndef INCLUDE_DROPS_CLASS_HPP_
#define INCLUDE_DROPS_CLASS_HPP_

#include "Bomb.hpp"

class Drop {
	public:
		virtual void setSpawnPoint(...)=0
		virtual	void getEffect(...)=0;
		virtual void ~Drop()=0;
		virtual void setSymbol(char symbol)=0;
		virtual char getSymol()=0;
	private:
		std::pair<int, int>		_xy;
		char					_symbol;
};

#endif

