#include <Sound.hpp>

Sound::Sound() : _musicVol(1.0f), _FXVol(1.0f) {
	this->_engine = irrklang::createIrrKlangDevice();
	if (!this->_engine)
		std::cerr << "Sound was unable to start\n";
	else
		_menuMusic = _engine->addSoundSourceFromFile("resources/sounds/DeathWave.wav");
	std::cout << "Sound Constructed\n";
}

Sound::Sound(int musicVol, int FXVol) : _musicVol(musicVol / 100), _FXVol(FXVol / 100) {
	std::cout << "Sound Constructed\n";
}

Sound::Sound(Sound const & src) {
	std::cout << "Sound Copy-Constructed\n";
	*this = src;
}

Sound::~Sound() {
	this->_engine->drop();
	std::cout << "Sound De-Constructed\n";
}

Sound &					Sound::operator=(Sound const & src) {
	this->_musicVol = src.getMusicVol();
	this->_FXVol = src.getFXVol();
	return (*this);
}

irrklang::ISoundEngine	*Sound::getEngine() {
	return (_engine);
}

irrklang::ISoundSource	*Sound::getMenuMusic() {
	return (_menuMusic);
}

int 					Sound::getMusicVol() const {
	return (this->_musicVol);
}

void					Sound::setMusicVol(const int newVol) {
	this->_musicVol = newVol;
}

int 					Sound::getFXVol() const {
	return (this->_FXVol);
}

void					Sound::setFXVol(const int newVol) {
	this->_FXVol = newVol;
}

void					Sound::startMenuMusic() {
	std::cout << "Starting menuMusic\n";
	this->_engine->play2D(this->_menuMusic, true);
	std::cout << "Menu Music playing.\n";
}

void					Sound::stopMenuMusic() {
	std::cout << "Stopping menuMusic\n";
	if (this->_engine && this->_menuMusic)
        this->_engine->removeSoundSource(this->_menuMusic);
	std::cout << "Menu Music stopped.\n";
}