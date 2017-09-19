#ifndef SOUND_HPP
#define SOUND_HPP

#include <unistd.h>
#include <iostream>
#include <irrKlang.h>
#include <Exceptions.hpp>

class Sound {
public:
	Sound();
	Sound(float musicVol, float fxVol);
	Sound(float musicVol, float FXVol, bool verbose);
	~Sound();
	Sound(Sound const & src);
	Sound &					operator=(Sound const &src);
	float					getMusicVol() const;
	void					setMusicVol(const float newVol);
	float					getFXVol() const;
	void					setFXVol(const float newVol);
	bool					getVerbose() const;
	void					setVerbose(const bool newV);
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
	bool					_verbose;

	irrklang::ISoundSource	*_menuMusic;
	irrklang::ISound		*_menuMusicS;
	irrklang::ISoundSource	*_gameMusic;
	irrklang::ISound		*_gameMusicS;

	irrklang::ISoundSource	*_menuPass;
	irrklang::ISound		*_menuPassS;
	irrklang::ISoundSource	*_menuFail;
	irrklang::ISound		*_menuFailS;
	irrklang::ISoundSource	*_menuHover;
	irrklang::ISound		*_menuHoverS;
	irrklang::ISoundSource	*_menuClick;
	irrklang::ISound		*_menuClickS;
	irrklang::ISoundSource	*_menuLimit;
	irrklang::ISound		*_menuLimitS;
	irrklang::ISoundSource	*_gameSaved;
	irrklang::ISound		*_gameSavedS;
	irrklang::ISoundSource	*_playerSpawn;
	irrklang::ISound		*_playerSpawnS;
	irrklang::ISoundSource	*_playerWalk;
	irrklang::ISound		*_playerWalkS;
	irrklang::ISoundSource	*_enemySpawn;
	irrklang::ISound		*_enemySpawnS;
	irrklang::ISoundSource	*_enemyWalk;
	irrklang::ISound		*_enemyWalkS;
	irrklang::ISoundSource	*_plantBomb;
	irrklang::ISound		*_plantBombS;
	irrklang::ISoundSource	*_detonateBomb;
	irrklang::ISound		*_detonateBombS;
	irrklang::ISoundSource	*_dropDrop;
	irrklang::ISound		*_dropDropS;
	irrklang::ISoundSource	*_pickupDrop;
	irrklang::ISound		*_pickupDropS;
};

#endif
