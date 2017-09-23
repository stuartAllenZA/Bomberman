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
	Enemy(std::pair<float, float> xy, int speed, int health, int lives);
	Enemy(std::pair<float, float> xy, int speed, int health);
	Enemy(std::pair<float, float> xy, int lives);
	Enemy(std::pair<float, float> xy);
	Enemy(int lives);
	Enemy();
	Enemy(Enemy const & src);
	~Enemy();
	Enemy &	operator=(Enemy const & src);
	std::pair<float, float>	getNewCoOrd() const;
	void					setNewCoOrd(const std::pair<float, float> newCoOrd);
	void					determineNewCoOrds(std::pair<float, float> playerPos, std::vector<char> unable);
	bool					checkUnable(std::vector<char> unable, char dir) const;
	void					attack();

private:
	std::pair<float, float> _newCoOrd;
};

std::ostream &					operator<<(std::ostream & o, Enemy const & rhs);

#endif
