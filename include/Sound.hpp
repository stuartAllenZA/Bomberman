#ifndef SOUND_HPP
#define SOUND_HPP

#include <iostream>
#include <irrKlang.h>
#include "Exceptions.hpp"

//	TODO:
//	1. Create member function to configure listener properties
//	https://stackoverflow.com/questions/7861306/clarification-on-openal-listener-orientation

class Sound {
public:
	Sound();
	Sound(int musicVol, int fxVol);
	~Sound();
	Sound(Sound const & src);
	Sound &		operator=(Sound const &src);
	irrklang::ISoundEngine	*getEngine();
	irrklang::ISoundSource	*getMenuMusic();
	int						getMusicVol() const;
	void					setMusicVol(const int newVol);
	int						getFXVol() const;
	void					setFXVol(const int newVol);
	void					startMenuMusic();
	void					stopMenuMusic();

private:
	irrklang::ISoundEngine	*_engine;
	irrklang::ISoundSource	*_menuMusic;
	float					_musicVol;
	float					_FXVol;
};

#endif
