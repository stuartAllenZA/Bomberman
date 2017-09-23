#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>

// Add variable checklist
//		1. Getter & Setter
//		1. Constructor & = operator
//		1. Game::loadProfile
//		3. Game::saveProfile

class Settings
{
public:
	Settings();
	Settings(Settings const & src);
	~Settings();
	Settings &			operator=(Settings const & src);
	std::pair<int, int>	getResolution() const;
	void				setResolution(const std::pair<int, int> wh);
	std::string			getLastPlayer() const;
	void				setLastPlayer(const std::string newLastPlayer);
	bool				getWindowed() const;
	void				setWindowed(const bool newWin);
	int					getXPos() const;
	void				setXPos(const int newXPos);
	int					getYPos() const;
	void				setYPos(const int newYPos);
	int					getUpKey() const;
	void				setUpKey(const int newKey);
	int					getDownKey() const;
	void				setDownKey(const int newKey);
	int					getLeftKey() const;
	void				setLeftKey(const int newKey);
	int					getRightKey() const;
	void				setRightKey(const int newKey);
	int					getActionKey() const;
	void				setActionKey(const int newKey);
	int					getAcceptKey() const;
	void				setAcceptKey(const int newKey);
	int					getEscapeKey() const;
	void				setEscapeKey(const int newKey);
	float				getMusicVol() const;
	void				setMusicVol(const float newVol);
	float				getFXVol() const;
	void				setFXVol(const float newVol);

	int					getResolutionX() const;
	int					getResolutionY() const;

private:
	std::pair<int, int>	_resolution;
	std::string 		_lastPlayer;
	bool				_windowed;
	int					_xPos;
	int					_yPos;
	int					_upKey;
	int					_downKey;
	int					_leftKey;
	int					_rightKey;
	int					_actionKey;
	int					_acceptKey;
	int					_escapeKey;
	float				_musicVol;
	float				_FXVol;
};

std::ostream &					operator<<(std::ostream & o, Settings const & rhs);

#endif