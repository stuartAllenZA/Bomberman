#ifndef INCLUDE_ENEMY_DROP_HPP_
#define INCLUDE_ENEMY_DROP_HPP_

#include "Drops.hpp"

class EnemyDrop : public Drop {
	public:
		EnemyDrop();
		~EnemyDrop();
		EnemyDrop(EnemyDrop const & src);
		EnemyDrop	&operator=(EnemyDrop const &src);
	private:
};

#endif

