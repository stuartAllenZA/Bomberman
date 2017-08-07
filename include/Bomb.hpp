#ifndef INCLUDE_BOMB_CLASS_HPP_
#define INCLUDE_BOMB_CLASS_HPP_

class Bomb {
	public:
		Bomb();
		~Bomb();
		Bomb(Bomb const & src);
		Bomb	&operator=(Bomb const &src);
		void	setEffect(Drop	&drop);

	private:
		std::pair<int, int>		_xy;
		int						_blastRange;
		int						_timeToDetonate;
		int						_numberCanLaunch;
		bool					_canBeRemoteDetonated;
};

#endif

