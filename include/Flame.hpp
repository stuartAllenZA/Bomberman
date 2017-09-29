#ifndef FLAME_HPP
#define FLAME_HPP

#include <iostream>

class Flame {
public:
	Flame(std::pair<float, float> xy, std::uint64_t timeToDie);
	~Flame();
	Flame(Flame const & src);
	Flame &				operator=(Flame const &src);
	std::pair<float, float>	getXY() const;
	void				setXY(const std::pair<float, float> xy);
	std::uint64_t		getTimeToDie() const;
	void				setTimeToDie(const std::uint64_t newTTD);

private:
	std::pair<float, float>	_xy;
	std::uint64_t			_timeToDie;
};

#endif
