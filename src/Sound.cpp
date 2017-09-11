#include <Sound.hpp>

Sound::Sound() : _device(NULL), _context(NULL) {
	this->_listenerOri[2] = -1.0;
	this->_listenerOri[4] = 1.0;
	std::cout << "Sound Constructed\n";
}

Sound::Sound(int musicVol, int FXVol) : _device(NULL), _context(NULL), _musicVol(musicVol), _FXVol(FXVol) {
	this->_listenerOri[2] = -1.0;
	this->_listenerOri[4] = 1.0;
	std::cout << "Sound Constructed\n";
}

Sound::Sound(Sound const & src) {
	std::cout << "Sound Copy-Constructed\n";
	*this = src;
}

Sound::~Sound() {
	alcMakeContextCurrent(NULL);
	alcDestroyContext(this->_context);
	alcCloseDevice(this->_device);
	std::cout << "Sound De-Constructed\n";
}

Sound &			Sound::operator=(Sound const & src) {
	this->_error = src.getError();
	this->_musicSource = src.getMusicSource();
	this->_musicBuffer = src.getMusicBuffer();
	this->_sourcePos[0] = src.getSourcePos(0);
	this->_sourcePos[1] = src.getSourcePos(1);
	this->_sourcePos[2] = src.getSourcePos(2);
	this->_sourceVel[0] = src.getSourceVel(0);
	this->_sourceVel[1] = src.getSourceVel(1);
	this->_sourceVel[2] = src.getSourceVel(2);
	this->_listenerPos[0] = src.getListenerPos(0);
	this->_listenerPos[1] = src.getListenerPos(1);
	this->_listenerPos[2] = src.getListenerPos(2);
	this->_listenerVel[0] = src.getListenerVel(0);
	this->_listenerVel[1] = src.getListenerVel(1);
	this->_listenerVel[2] = src.getListenerVel(2);
	this->_listenerOri[0] = src.getListenerOri(0);
	this->_listenerOri[1] = src.getListenerOri(1);
	this->_listenerOri[2] = src.getListenerOri(2);
	this->_listenerOri[3] = src.getListenerOri(3);
	this->_listenerOri[4] = src.getListenerOri(4);
	this->_listenerOri[5] = src.getListenerOri(5);
	this->_musicVol = src.getMusicVol();
	this->_FXVol = src.getFXVol();
	return (*this);
}

ALenum			Sound::getError() const {
	return (this->_error);
}

void			Sound::setError(const ALenum newError) {
	this->_error = newError;
}

ALuint			Sound::getMusicSource() const {
	return (this->_musicSource);
}

void			Sound::setMusicSource(const ALuint newMusicSource) {
	this->_musicSource = newMusicSource;
}

ALuint			Sound::getMusicBuffer() const {
	return (this->_musicBuffer);
}

void			Sound::setMusicBuffer(const ALuint newMusicBuffer) {
	this->_musicBuffer = newMusicBuffer;
}

ALfloat			Sound::getSourcePos(const int index) const {
	return (this->_sourcePos[index]);
}

void			Sound::setSourcePos(const int index, const float newValue) {
	this->_sourcePos[index] = newValue;
}

ALfloat			Sound::getSourceVel(const int index) const {
	return (this->_sourceVel[index]);
}

void			Sound::setSourceVel(const int index, const float newValue) {
	this->_sourceVel[index] = newValue;
}

ALfloat			Sound::getListenerPos(const int index) const {
	return (this->_listenerPos[index]);
}

void			Sound::setListenerPos(const int index, const float newValue) {
	this->_listenerPos[index] = newValue;
}

ALfloat			Sound::getListenerVel(const int index) const {
	return (this->_listenerVel[index]);
}

void			Sound::setListenerVel(const int index, const float newValue) {
	this->_listenerVel[index] = newValue;
}

ALfloat			Sound::getListenerOri(const int index) const {
	return (this->_listenerOri[index]);
}

void			Sound::setListenerOri(const int index, const float newValue) {
	this->_listenerOri[index] = newValue;
}

int 			Sound::getMusicVol() const {
	return (this->_musicVol);
}

void			Sound::setMusicVol(const int newVol) {
	this->_musicVol = newVol;
}

int 			Sound::getFXVol() const {
	return (this->_FXVol);
}

void			Sound::setFXVol(const int newVol) {
	this->_FXVol = newVol;
}

void			Sound::checkForErrors() {
	this->_error = alGetError();
	if (this->_error != AL_NO_ERROR)
	{
		std::cout << "Sound encountered an error: " << static_cast<int>(this->_error) << std::endl;
		if (this->_error == AL_INVALID_NAME)
			throw (Exceptions::SoundGeneralError(static_cast<int>(this->_error), "AL_INVALID_NAME"));
		else if (this->_error != AL_INVALID_OPERATION)
			throw (Exceptions::SoundGeneralError(static_cast<int>(this->_error), "AL_INVALID_OPERATION"));
		else if (this->_error != AL_INVALID_ENUM)
			throw (Exceptions::SoundGeneralError(static_cast<int>(this->_error), "AL_INVALID_ENUM"));
		else if (this->_error != AL_INVALID_VALUE)
			throw (Exceptions::SoundGeneralError(static_cast<int>(this->_error), "AL_INVALID_VALUE"));
		else if (this->_error != AL_OUT_OF_MEMORY)
			throw (Exceptions::SoundGeneralError(static_cast<int>(this->_error), "AL_OUT_OF_MEMORY"));
		else
			throw (Exceptions::SoundGeneralError(static_cast<int>(this->_error), "Unknown error code"));
	}
}

void			Sound::startBackgroundMusic() {
	std::cout << "Creating WAVFile object\n";
	WAVFile backgroundMusic = WAVFile("resources/sounds/DeathWave.wav");
	//WAVFile backgroundMusic = WAVFile("~/Downloads/harp.wav");
	backgroundMusic.initWAVFile();
	std::cout << backgroundMusic;
	std::cout << "Init OpenAL buffer and source, check for errors\n";
	alGenBuffers((ALuint)1, &this->_musicBuffer);
	alGenSources((ALuint)1, &this->_musicSource);
	checkForErrors();
	std::cout << "Fill buffer using data from WAVFile object\n";
	alBufferData(this->_musicBuffer, backgroundMusic.getFormat(), backgroundMusic.getData(), backgroundMusic.getDataSize(), backgroundMusic.getSampleRate());
	checkForErrors();
	//Set modify positiions to accound for volume
	//processMusicVolume();
	std::cout << "Configure listener\n";
	alListenerfv(AL_POSITION, this->_listenerPos);
	checkForErrors();
	std::cout << "1\n";
	alListenerfv(AL_VELOCITY, this->_listenerVel);
	checkForErrors();
	std::cout << "2\n";
	alListenerfv(AL_ORIENTATION, this->_listenerOri);
	checkForErrors();
	std::cout << "3Configure source\n";
	alSourcei(this->_musicSource, AL_BUFFER, this->_musicBuffer);
	checkForErrors();
	std::cout << "4\n";
	alSourcef(this->_musicSource, AL_PITCH, 1.0f);
	checkForErrors();
	std::cout << "5\n";
	alSourcef(this->_musicSource, AL_GAIN, 1.0f);
	checkForErrors();
	std::cout << "6\n";
	alSourcefv(this->_musicSource, AL_POSITION, this->_sourcePos);
	checkForErrors();
	std::cout << "7\n";
	alSourcefv(this->_musicSource, AL_VELOCITY, this->_sourceVel);
	checkForErrors();
	std::cout << "8\n";
	alSourcei(this->_musicSource, AL_LOOPING, AL_FALSE);
	checkForErrors();
	std::cout << "9\n";
	alSourcePlay(this->_musicSource);
	std::cout << "Sleeping for 20 seconds\n";
	sleep(20);
	//alSourcePause(this->_musicSource);
	//alSourceStop(this->_musicSource);
	alDeleteSources(1, &this->_musicSource);
	alDeleteBuffers(1, &this->_musicBuffer);
}

// void			Sound::processMusicVolume() {
// 	//Music volume is handeled by multiplying the current X value of listener position
// 	//by 1/(musicVol /100). If the distance is 0, it is made musicVol/100
// 	ALfloat tempListenerPos;
// 	float musicMultiplier;

// 	tempListenerPos = this->_listenerPos;
// 	musicMultiplier = 1 / (this->_musicVol / 100);
// 	if (this->_listenerPos[0] == 0.0)
// 		this->_listenerPos = {this->_musicVol / 100, tempListenerPos[1], tempListenerPos[2]};
// 	else
// 		this->_listenerPos = {tempListenerPos[0] * musicMultiplier, tempListenerPos[1], tempListenerPos[2]};
// }

void			Sound::initSound() {
	this->_device = const_cast<ALCdevice *>(alcOpenDevice(NULL));
	// this->_sourcePos = {0.0, 0.0, 0.0};
	// this->_sourceVel = {0.0, 0.0, 0.0};
	// this->_listenerPos = {0.0, 0.0, 0.0};
	// this->_listenerVel = {0.0, 0.0, 0.0};
	if (!this->_device)
		throw (Exceptions::SoundDeviceInitError()); //Throw if device could not be initialized
	alGetError(); //Clears the error stack
	this->_context = const_cast<ALCcontext *>(alcCreateContext(this->_device, NULL));
	if (!alcMakeContextCurrent(this->_context) || !this->_context)
		throw (Exceptions::SoundContextInitError()); //Throw if device could not be initialized
	checkForErrors();
	std::cout << "Sound Sucsessfully Initialized\n";
}
