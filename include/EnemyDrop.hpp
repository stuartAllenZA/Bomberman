#ifndef INCLUDE_ENEMY_DROP_HPP_
#define INCLUDE_ENEMY_DROP_HPP_

#include <Drop.hpp>

class EnemyDrop : public Drop {
	public:
		EnemyDrop(std::pair<float, float> xy);
		~EnemyDrop();
		EnemyDrop(EnemyDrop const & src);
		EnemyDrop	&operator=(EnemyDrop const &src);
	private:
};

#endif
