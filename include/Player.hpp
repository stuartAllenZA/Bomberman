#ifndef Player_HPP
#define Player_HPP

#include <Character.hpp>

class Player : public Character
{
public:
	Player(std::string name);
	Player(Player const & src);
	~Player();
	Player &	operator=(Player const & src);
	std::string	getName() const;
	void		setName(const std::string newName);
	int			getLevel() const;
	void		setLevel(const int newLevel);
	int			getExperience() const;
	void		setExperience(const int newExp);

private:
	std::string	_name;
	int			_level;
	int			_experience;
	
};

#endif