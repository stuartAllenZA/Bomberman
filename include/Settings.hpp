#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>
#include <iostream>
#include <vector>

// Add variable checklist
//		1. Getter & Setter
//		1. Constructor & = operator
//		1. Game::loadSettings
//		3. Game::saveSettings

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
	int					getMusicVol() const;
	void				setMusicVol(const int newVol);
	int					getFXVol() const;
	void				setFXVol(const int newVol);

	int					getResolutionX() const;
	int					getResolutionY() const;

private:
	std::pair<int, int>	_resolution;
	std::string 		_lastPlayer;
	bool				_windowed;
	int					_upKey;
	int					_downKey;
	int					_leftKey;
	int					_rightKey;
	int					_actionKey;
	int					_musicVol;
	int					_FXVol;
};

std::ostream &					operator<<(std::ostream & o, Settings const & rhs);

#endif