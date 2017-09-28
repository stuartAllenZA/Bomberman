#ifndef BOMB_HPP
#define BOMB_HPP

#include <iostream>

class Bomb {
public:
	Bomb(std::pair<float, float> xy, int blastRange, std::uint64_t timeToDetonate, bool canBeRemoteDetonated);
	~Bomb();
	Bomb(Bomb const & src);
	Bomb &				operator=(Bomb const &src);
	std::pair<float, float>	getXY() const;
	void				setXY(const std::pair<float, float> xy);
	int					getBlastRange() const;
	void				setBlastRange(const int newBlastRange);
	std::uint64_t		getTimeToDetonate() const;
	void				setTimeToDetonate(const std::uint64_t newTTD);
	bool				getCanBeRemoteDetonated() const;
	void				setCanBeRemoteDetonated(const bool newCBRD);

private:
	std::pair<float, float>	_xy;
	int						_blastRange;
	std::uint64_t			_timeToDetonate;
	bool					_canBeRemoteDetonated;
};

#endif
