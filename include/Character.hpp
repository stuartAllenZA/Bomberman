#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <iostream>
#include <vector>

class Character
{
public:
	Character(std::pair<float, float> xy, float speed, int health, int lives, char ori);
	Character(std::pair<float, float> xy, float speed, int health, int lives);
	Character(std::pair<float, float> xy, float speed, int health, char ori);
	Character(std::pair<float, float> xy, float speed, int health);
	Character(std::pair<float, float> xy, float lives);
	Character(std::pair<float, float> xy);
	Character(int lives);
	Character();
	Character(Character const & src);
	virtual ~Character() =0;
	Character &				operator=(Character const & src);
	std::pair<float, float>	getXY() const;
	void					setXY(const std::pair<float, float> xy);
	float					getSpeed() const;
	void					setSpeed(const float newSpeed);
	int						getHealth() const;
	void					setHealth(const int newHealth);
	int						getLives() const;
	void					setLives(const int newLives);
	char					getOri() const;
	void					setOri(const char newOri);
	float					getSize() const;
	void					setSize(const float newSize);
	
protected:
	std::pair<float, float>	_xy;
	float					_speed;
	int						_health;
	int						_lives;
	char					_ori;
	float					_size;
};

#endif