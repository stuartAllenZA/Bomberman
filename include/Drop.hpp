#ifndef DROP_HPP
#define DROP_HPP

#include <iostream>

enum class DropType {
	LEVEL_HATCH,
	FLAME_EXT,
	BOMB_ADD,
	ENEMY_SPAWN
};

class Drop {
public:
	Drop();
	Drop(std::pair<float, float> xy);
	virtual ~Drop()=0;
	Drop(Drop const & src);
	Drop	&			operator=(Drop const &src);
	std::pair<float, float>	getXY() const;
	void				setXY(const std::pair<float, float> xy);
	DropType			getDropType() const;
	void				setDropType(const DropType newType);

protected:
	std::pair<float, float>		_xy;
	DropType					_type;
};

#endif

