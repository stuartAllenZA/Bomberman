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
	void					pauseMenuMusic();
	void					resumeMenuMusic();
	void					stopMenuMusic();
	void					startGameMusic();
	void					pauseGameMusic();
	void					resumeGameMusic();
	void					stopGameMusic();
	void					startCreditsMusic();
	void					pauseCreditsMusic();
	void					resumeCreditsMusic();
	void					stopCreditsMusic();
	void					playMenuPass();
	void					playMenuFail();
	void					playMenuHover();
	void					playMenuClick();
	void					playMenuKeypress();
	void					playMenuLimit();
	void					playGameSaved();
	void					playPlayerSpawn();
	void					playPlayerWalk();
	void					playPlayerHit();
	void					playEnemySpawn();
	void					playEnemyWalk();
	void					playEnemyHit();
	void					playPlantBomb();
	void					playDetonateBomb();
	void					playBoxDrop();
	void					playPickupExtraBomb();
	void					playPickupRangeExtend();
	void					playPickupRemoteDet();
	void					playLevelComplete();

private:
	irrklang::ISoundEngine	*_engine;
	float					_musicVol;
	float					_FXVol;
	bool					_verbose;

	irrklang::ISoundSource	*_menuMusic;
	irrklang::ISound		*_menuMusicS;
	unsigned int			_menuMusicPauseTime;
	irrklang::ISoundSource	*_gameMusic;
	irrklang::ISound		*_gameMusicS;
	unsigned int			_gameMusicPauseTime;
	irrklang::ISoundSource	*_creditsMusic;
	irrklang::ISound		*_creditsMusicS;
	unsigned int			_creditsMusicPauseTime;

	irrklang::ISoundSource	*_menuPass;
	irrklang::ISoundSource	*_menuFail;
	irrklang::ISoundSource	*_menuHover;
	irrklang::ISoundSource	*_menuClick;
	irrklang::ISoundSource	*_menuKeypress;
	irrklang::ISoundSource	*_menuLimit;
	irrklang::ISoundSource	*_gameSaved;
	irrklang::ISoundSource	*_playerSpawn;
	irrklang::ISoundSource	*_playerWalk;
	irrklang::ISoundSource	*_playerHit;
	irrklang::ISoundSource	*_enemySpawn;
	irrklang::ISoundSource	*_enemyWalk;
	irrklang::ISoundSource	*_enemyHit;
	irrklang::ISoundSource	*_plantBomb;
	irrklang::ISoundSource	*_detonateBomb;
	irrklang::ISoundSource	*_boxDrop;
	irrklang::ISoundSource	*_pickupExtraBomb;
	irrklang::ISoundSource	*_pickupRangeExtend;
	irrklang::ISoundSource	*_pickupRemoteDet;
	irrklang::ISoundSource	*_levelComplete;
};

#endif
