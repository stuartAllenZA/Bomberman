#ifndef INCLUDE_DROPS_CLASS_HPP_
#define INCLUDE_DROPS_CLASS_HPP_

#include "Bomb.hpp"

class Drop {
public:
	virtual void		~Drop()=0;
	std::pair<int, int>	getXY() const;
	void				setXY(const std::pair<int, int> xy);
	virtual void		setSymbol(const char symbol)=0;
	virtual char		getSymbol() const=0;
	virtual void		setSpawnPoint(...)=0
	virtual	void		getEffect(...) const=0;
private:
	std::pair<int, int>		_xy;
	char					_symbol;
};

#endif

