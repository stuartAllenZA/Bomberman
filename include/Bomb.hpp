#ifndef BOMB_HPP
#define BOMB_HPP

#include <iostream>

class Bomb {
public:
	Bomb(std::pair<float, float> xy, int blastRange, int timeToDetonate, bool canBeRemoteDetonated);
	~Bomb();
	Bomb(Bomb const & src);
	Bomb &				operator=(Bomb const &src);
	std::pair<float, float>	getXY() const;
	void				setXY(const std::pair<float, float> xy);
	int					getBlastRange() const;
	void				setBlastRange(const int newBlastRange);
	int					getTimeToDetonate() const;
	void				setTimeToDetonate(const int newTTD);
	bool				getCanBeRemoteDetonated() const;
	void				setCanBeRemoteDetonated(const bool newCBRD);

private:
	std::pair<float, float>	_xy;
	int						_blastRange;
	int						_timeToDetonate;
	bool					_canBeRemoteDetonated;
};

#endif
