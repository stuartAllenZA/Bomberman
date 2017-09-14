#ifndef SOUND_HPP
#define SOUND_HPP

#include <unistd.h>
#include <iostream>
#include <irrKlang.h>
#include "Exceptions.hpp"

class Sound {
public:
	Sound();
	Sound(int musicVol, int fxVol);
	~Sound();
	Sound(Sound const & src);
	Sound &					operator=(Sound const &src);
	int						getMusicVol() const;
	void					setMusicVol(const int newVol);
	int						getFXVol() const;
	void					setFXVol(const int newVol);
	void					init();
	void					updateMusicVol();
	void					updateFXVol();
	void					startMenuMusic();
	void					stopMenuMusic();
	void					startGameMusic();
	void					stopGameMusic();
	void					playMenuPass();
	void					playMenuFail();
	void					playMenuHover();
	void					playMenuClick();
	void					playMenuLimit();
	void					playGameSaved();
	void					playPlayerSpawn();
	void					playPlayerWalk();
	void					playEnemySpawn();
	void					playEnemyWalk();
	void					playPlantBomb();
	void					playDetonateBomb();
	void					playDropDrop();
	void					playPickupDrop();

private:
	irrklang::ISoundEngine	*_engine;
	float					_musicVol;
	float					_FXVol;

	irrklang::ISoundSource	*_menuMusic;
	irrklang::ISoundSource	*_gameMusic;

	irrklang::ISoundSource	*_menuPass;
	irrklang::ISoundSource	*_menuFail;
	irrklang::ISoundSource	*_menuHover;
	irrklang::ISoundSource	*_menuClick;
	irrklang::ISoundSource	*_menuLimit;
	irrklang::ISoundSource	*_gameSaved;
	irrklang::ISoundSource	*_playerSpawn;
	irrklang::ISoundSource	*_playerWalk;
	irrklang::ISoundSource	*_enemySpawn;
	irrklang::ISoundSource	*_enemyWalk;
	irrklang::ISoundSource	*_plantBomb;
	irrklang::ISoundSource	*_detonateBomb;
	irrklang::ISoundSource	*_dropDrop;
	irrklang::ISoundSource	*_pickupDrop;
};

#endif
