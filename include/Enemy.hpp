#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <Character.hpp>
// Add variable checklist

//		1. Getter & Setter
//		2. Add to << overload
//		3. Game::loadEnemy
//		4. Game::saveEnemy

class Enemy : public Character
{
public:
	Enemy(std::pair<int, int> xy, int speed, int health, int lives);
	Enemy(std::pair<int, int> xy, int speed, int health);
	Enemy(std::pair<int, int> xy, int lives);
	Enemy(std::pair<int, int> xy);
	Enemy(int lives);
	Enemy();
	Enemy(Enemy const & src);
	~Enemy();
	Enemy &	operator=(Enemy const & src);

private:
};

std::ostream &					operator<<(std::ostream & o, Enemy const & rhs);

#endif
