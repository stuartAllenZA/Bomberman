#ifndef Player_HPP
#define Player_HPP

#include "Character.hpp"

// Add variable checklist
//		1. Getter & Setter
//		1. Game::loadPlayer
//		3. Game::savePlayer

class Player : public Character
{
public:
	Player(std::pair<int, int> xy, int lives, std::string name);
	Player(std::pair<int, int> xy, std::string name);
	Player(int lives, std::string name);
	Player(std::string name);
	Player(Player const & src);
	~Player();
	Player &	operator=(Player const & src);
	std::string	getFileLocation() const;
	void		setFileLocation(const std::string newLocation);
	std::string	getName() const;
	void		setName(const std::string newName);
	int			getLevel() const;
	void		setLevel(const int newLevel);
	int			getExperience() const;
	void		setExperience(const int newExp);

private:
	std::string	_fileLocation;
	std::string	_name;
	int			_level;
	int			_experience;
	
};

#endif
