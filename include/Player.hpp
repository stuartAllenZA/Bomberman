#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <Character.hpp>
// Add variable checklist

//	1. Getter & Setter
//	2. Add to << overload
//	3. Game::loadPlayer
//	4. Game::savePlayer

class Player : public Character
{
public:
	Player(std::pair<float, float> xy, int lives, std::string name);
	Player(std::pair<float, float> xy, std::string name);
	Player(int lives, std::string name);
	Player(std::string name);
	Player();
	Player(Player const & src);
	~Player();
	Player &	operator=(Player const & src);
	std::string	getFileLocation() const;
	void		setFileLocation(const std::string newLocation);
	std::string	getName() const;
	void		setName(const std::string newName);
	int			getProgress() const;
	void		setProgress(const int newProgress);
	int			getLevel() const;
	void		setLevel(const int newLevel);
	int			getExperience() const;
	void		setExperience(const int newExp);
	int			getNumberOfBombs() const;
	void		setNumberOfBombs(const int bombs);
	int			getDifficulty() const;
	void		setDifficulty(const int newDifficulty);
	float 		getBlocksPerSec() const;
	void		setBlocksPerSec(const float newBlocksPerSec);
	float 		getPlayerWidth() const;
	void		setPlayerWidth(const float newPlayerWidth);

private:
	std::string	_fileLocation;
	std::string	_name;
	int			_progress;
	int			_level;
	int			_experience;
	int			_numberOfBombs;
	int			_difficulty;
	float 		_blocksPerSec;
};

std::ostream &					operator<<(std::ostream & o, Player const & rhs);

#endif
