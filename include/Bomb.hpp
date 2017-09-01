#ifndef INCLUDE_BOMB_CLASS_HPP_
#define INCLUDE_BOMB_CLASS_HPP_

#include <iostream>

class Bomb {
public:
	Bomb(std::pair<int, int> xy, int blastRange, int timeToDetonate, bool canBeRemoteDetonated);
	~Bomb();
	Bomb(Bomb const & src);
	Bomb &				operator=(Bomb const &src);
	std::pair<int, int>	getXY() const;
	void				setXY(const std::pair<int, int> xy);
	int					getBlastRange() const;
	void				setBlastRange(const int newBlastRange);
	int					getTimeToDetonate() const;
	void				setTimeToDetonate(const int newTTD);
	bool				getCanBeRemoteDetonated() const;
	void				setCanBeRemoteDetonated(const bool newCBRD);

private:
	std::pair<int, int>		_xy;
	int						_blastRange;
	int						_timeToDetonate;
	bool					_canBeRemoteDetonated;
};

#endif
