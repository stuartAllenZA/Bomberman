#include <Sound.hpp>

Sound::Sound() : _musicVol(1.0), _FXVol(1.0), _verbose(false) {
	if (this->_verbose)
		std::cout << "Sound Constructed\n";
}

Sound::Sound(float musicVol, float FXVol) : _musicVol(musicVol), _FXVol(FXVol), _verbose(false) {
	if (this->_verbose)
		std::cout << "Sound Constructed\n";
}

Sound::Sound(float musicVol, float FXVol, bool verbose) : _musicVol(musicVol), _FXVol(FXVol), _verbose(verbose) {
	if (this->_verbose)
		std::cout << "Sound Constructed\n";
}

Sound::Sound(Sound const & src) {
	if (this->_verbose)
		std::cout << "Sound Copy-Constructed\n";
	*this = src;
}

Sound::~Sound() {
	this->_engine->drop();
	if (this->_verbose)
		std::cout << "Sound De-Constructed\n";
}

Sound &					Sound::operator=(Sound const & src) {
	this->_musicVol = src.getMusicVol();
	this->_FXVol = src.getFXVol();
	this->_verbose = src.getVerbose();
	return (*this);
}

float 					Sound::getMusicVol() const {
	return (this->_musicVol);
}

void					Sound::setMusicVol(const float newVol) {
	if (newVol < 0.1)
		this->_musicVol = 0.0;
	else
		this->_musicVol = newVol;
}

float 					Sound::getFXVol() const {
	return (this->_FXVol);
}

void					Sound::setFXVol(const float newVol) {
	if (newVol < 0.1)
		this->_FXVol = 0.0;
	else
	this->_FXVol = newVol;
}

bool					Sound::getVerbose() const {
	return (this->_verbose);
}

void					Sound::setVerbose(const bool newV) {
	this->_verbose = newV;
}

void					Sound::init() {
	if (this->_verbose)
		std::cout << "Initializing Sound." << std::endl;
	chdir(".irrKlang/");
	this->_engine = irrklang::createIrrKlangDevice();
	chdir("..");
	if (!this->_engine)
		throw (Exceptions::SoundDeviceInitError());
	else {
		this->_menuMusic = _engine->addSoundSourceFromFile("resources/sounds/menuMusic.wav");
		this->_gameMusic = _engine->addSoundSourceFromFile("resources/sounds/gameMusic.mp3");
		this->_menuPass = _engine->addSoundSourceFromFile("resources/sounds/menuPass.mp3");
		this->_menuFail = _engine->addSoundSourceFromFile("resources/sounds/menuFail.wav");
		this->_menuHover = _engine->addSoundSourceFromFile("resources/sounds/menuHover.wav");
		this->_menuClick = _engine->addSoundSourceFromFile("resources/sounds/menuClick.mp3");
		this->_menuLimit = _engine->addSoundSourceFromFile("resources/sounds/menuLimit.wav");
		this->_gameSaved = _engine->addSoundSourceFromFile("resources/sounds/gameSaved.wav");
		this->_playerSpawn = _engine->addSoundSourceFromFile("resources/sounds/playerSpawn");
		this->_playerWalk = _engine->addSoundSourceFromFile("resources/sounds/playerWalk.wav");
		this->_enemySpawn = _engine->addSoundSourceFromFile("resources/sounds/enemySpawn");
		this->_enemyWalk = _engine->addSoundSourceFromFile("resources/sounds/enemyWalk");
		this->_plantBomb = _engine->addSoundSourceFromFile("resources/sounds/plantBomb");
		this->_detonateBomb = _engine->addSoundSourceFromFile("resources/sounds/detonateBomb");
		this->_dropDrop = _engine->addSoundSourceFromFile("resources/sounds/dropDrop.wav");
		this->_pickupDrop = _engine->addSoundSourceFromFile("resources/sounds/pickupDrop.wav");
		this->updateMusicVol();
		this->updateFXVol();
		if (this->_verbose)
			std::cout << "Sound Sucsesfully Initialized." << std::endl;
	}
}

void					Sound::updateMusicVol() {
	if (this->_menuMusic) {
		std::cout << "Updating musicMenu Default Vol" << std::endl;
		this->_menuMusic->setDefaultVolume(this->_musicVol);
	}
	if (this->_gameMusic) {
		std::cout << "Updating gameMenu Default Vol" << std::endl;
		this->_gameMusic->setDefaultVolume(this->_musicVol);
	}
	if (this->_menuMusicS) {
		std::cout << "Updating musicMenu Vol to: " << this->_musicVol << std::endl;
		this->_menuMusicS->setVolume(this->_musicVol);
	}
	if (this->_gameMusicS) {
		std::cout << "Updating gameMenu Vol to: " << this->_musicVol << std::endl;
		this->_gameMusicS->setVolume(this->_musicVol);
	}
}

void					Sound::updateFXVol() {
	if (this->_menuPass)
		this->_menuPass->setDefaultVolume(this->_FXVol);
	if (this->_menuFail)
		this->_menuFail->setDefaultVolume(this->_FXVol);
	if (this->_menuHover)
		this->_menuHover->setDefaultVolume(this->_FXVol);
	if (this->_menuClick)
		this->_menuClick->setDefaultVolume(this->_FXVol);
	if (this->_playerSpawn)
		this->_playerSpawn->setDefaultVolume(this->_FXVol);
	if (this->_playerWalk)
		this->_playerWalk->setDefaultVolume(this->_FXVol);
	if (this->_enemySpawn)
		this->_enemySpawn->setDefaultVolume(this->_FXVol);
	if (this->_enemyWalk)
		this->_enemyWalk->setDefaultVolume(this->_FXVol);
	if (this->_plantBomb)
		this->_plantBomb->setDefaultVolume(this->_FXVol);
	if (this->_detonateBomb)
		this->_detonateBomb->setDefaultVolume(this->_FXVol);
	if (this->_dropDrop)
		this->_dropDrop->setDefaultVolume(this->_FXVol);
	if (this->_pickupDrop)
		this->_pickupDrop->setDefaultVolume(this->_FXVol);

	// if (this->_menuPassS)
	// 	this->_menuPassS->setVolume(this->_FXVol);
	// if (this->_menuFailS)
	// 	this->_menuFailS->setVolume(this->_FXVol);
	// if (this->_menuHoverS)
	// 	this->_menuHoverS->setVolume(this->_FXVol);
	// if (this->_menuClickS)
	// 	this->_menuClickS->setVolume(this->_FXVol);
	// if (this->_playerSpawnS)
	// 	this->_playerSpawnS->setVolume(this->_FXVol);
	// if (this->_playerWalkS)
	// 	this->_playerWalkS->setVolume(this->_FXVol);
	// if (this->_enemySpawnS)
	// 	this->_enemySpawnS->setVolume(this->_FXVol);
	// if (this->_enemyWalkS)
	// 	this->_enemyWalkS->setVolume(this->_FXVol);
	// if (this->_plantBombS)
	// 	this->_plantBombS->setVolume(this->_FXVol);
	// if (this->_detonateBombS)
	// 	this->_detonateBombS->setVolume(this->_FXVol);
	// if (this->_dropDropS)
	// 	this->_dropDropS->setVolume(this->_FXVol);
	// if (this->_pickupDropS)
	// 	this->_pickupDropS->setVolume(this->_FXVol);
}

void					Sound::startMenuMusic() {
	if (this->_verbose)
		std::cout << "Starting Menu Music\n";
	this->_menuMusicS = this->_engine->play2D(this->_menuMusic, true, false, true);
	if (this->_verbose)
		std::cout << "Menu Music playing.\n";
}

void					Sound::stopMenuMusic() {
	if (this->_verbose)
		std::cout << "Stopping Menu Music\n";
	if (this->_engine && this->_menuMusic) {
		this->_menuMusic->drop();
		this->_engine->removeSoundSource(this->_menuMusic);
		if (this->_verbose)
			std::cout << "Menu Music stopped.\n";
	}
}

void					Sound::startGameMusic() {
	if (this->_verbose)
		std::cout << "Starting Game Music\n";
	this->_gameMusicS = this->_engine->play2D(this->_gameMusic, true, false, true);
	if (this->_verbose)
		std::cout << "Game Music playing.\n";
}

void					Sound::stopGameMusic() {
	if (this->_verbose)
		std::cout << "Stopping Game Music\n";
	if (this->_engine && this->_gameMusic) {
		this->_gameMusic->drop();
		this->_engine->removeSoundSource(this->_gameMusic);
		if (this->_verbose)
			std::cout << "Game Music stopped.\n";
	}
}

void					Sound::playMenuPass() {
	if (this->_verbose)
		std::cout << "Playing Menu Pass\n";
	this->_menuPassS = this->_engine->play2D(this->_menuPass, false, false, true);
	this->_menuPassS->drop();
}

void					Sound::playMenuFail() {
	if (this->_verbose)
		std::cout << "Playing Menu Fail\n";
	this->_menuFailS = this->_engine->play2D(this->_menuFail, false, false, true);
	this->_menuFailS->drop();
}

void					Sound::playMenuHover() {
	if (this->_verbose)
		std::cout << "Playing Menu Hover\n";
	this->_menuHoverS = this->_engine->play2D(this->_menuHover, false, false, true);
	this->_menuHoverS->drop();
}

void					Sound::playMenuClick() {
	if (this->_verbose)
		std::cout << "Playing Menu Click\n";
	this->_menuClickS = this->_engine->play2D(this->_menuClick, false, false, true);
	this->_menuClickS->drop();
}

void					Sound::playMenuLimit() {
	if (this->_verbose)
		std::cout << "Playing Menu Limit\n";
	this->_menuLimitS = this->_engine->play2D(this->_menuLimit, false, false, true);
	this->_menuLimitS->drop();
}

void					Sound::playGameSaved() {
	if (this->_verbose)
		std::cout << "Playing Game Saved\n";
	this->_gameSavedS = this->_engine->play2D(this->_gameSaved, false, false, true);
	this->_gameSavedS->drop();
}

void					Sound::playPlayerSpawn() {
	if (this->_verbose)
		std::cout << "Playing Player Spawn\n";
	this->_playerSpawnS = this->_engine->play2D(this->_playerSpawn, false, false, true);
	this->_playerSpawnS->drop();
}

void					Sound::playPlayerWalk() {
	if (this->_verbose)
		std::cout << "Playing Player Walk\n";
	this->_playerWalkS = this->_engine->play2D(this->_playerWalk, false, false, true);
	this->_playerWalkS->drop();
}

void					Sound::playEnemySpawn() {
	if (this->_verbose)
		std::cout << "Playing Enemy Spawn\n";
	this->_enemySpawnS = this->_engine->play2D(this->_enemySpawn, false, false, true);
	this->_enemySpawnS->drop();
}

void					Sound::playEnemyWalk() {
	if (this->_verbose)
		std::cout << "Playing Enemy Walk\n";
	this->_enemyWalkS = this->_engine->play2D(this->_enemyWalk, false, false, true);
	this->_enemyWalkS->drop();
}

void					Sound::playPlantBomb() {
	if (this->_verbose)
		std::cout << "Playing Plant Bomb\n";
	this->_plantBombS = this->_engine->play2D(this->_plantBomb, false, false, true);
	this->_plantBombS->drop();
}

void					Sound::playDetonateBomb() {
	if (this->_verbose)
		std::cout << "Playing Detonate Bomb\n";
	this->_detonateBombS = this->_engine->play2D(this->_detonateBomb, false, false, true);
	this->_detonateBombS->drop();
}

void					Sound::playDropDrop() {
	if (this->_verbose)
		std::cout << "Playing Drop Drop\n";
	this->_dropDropS = this->_engine->play2D(this->_dropDrop, false, false, true);
	this->_dropDropS->drop();
}

void					Sound::playPickupDrop() {
	if (this->_verbose)
		std::cout << "Playing Pickup Drop\n";
	this->_pickupDropS = this->_engine->play2D(this->_pickupDrop, false, false, true);
	this->_pickupDropS->drop();
}