#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>
#include <iostream>
#include <vector>

class Settings
{
public:
	Settings();
	Settings(Settings const & src);
	~Settings();
	Settings &			operator=(Settings const & src);
	std::pair<int, int>	getResolution() const;
	void				setResolution(const std::pair<int, int> wh);
	bool				getWindowded() const;
	void				setWindowded(const bool newWin);
	int					getUpKey() const;
	void				setUpKey(const int newKey);
	int					getDownKey() const;
	void				setDownKey(const int newKey);
	int					getLeftKey() const;
	void				setLeftKey(const int newKey);
	int					getRightKey() const;
	void				setRightKey(const int newKey);
	int					getMusicVol() const;
	void				setMusicVol(const int newVol);
	int					getFXVol() const;
	void				setFXVol(const int newVol);

private:
	std::pair<int, int>	_resolution;
	bool				_windowed;
	int					_upKey;
	int					_downKey;
	int					_leftKey;
	int					_rightKey;
	int					_musicVol;
	int					_FXVol;	
};

#endif