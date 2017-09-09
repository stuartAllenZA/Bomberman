#include <Sound.hpp>

Sound::Sound() {
	this->_device = alcOpenDevice(NULL);
	if (!device)
		throw (Exceptions::SoundDeviceInitError()); //Throw if device could not be initialized
	alGetErrror(); //Clears the error stack
	this->_context = alcCreateContext(this->_device, NULL);
	if (!alcMakeContextCurrent(this->_context) || !this->_context)
		throw (Exceptions::SoundContextInitError()); //Throw if device could not be initialized
	checkForErrors();
	std::cout << "Sound Constructed\n";
}

Sound::Sound(Sound const & src) {
	std::cout << "Sound Copy-Constructed\n";
	*this = src;
}

Sound::~Sound() {
	std::cout << "Sound De-Constructed\n";
}

ALCdevice *		Sound::getDevice() const {
	return (this->_device);
}

void			Sound::setDevice(const ALCdevice *newDevice) {
	this->_device = newDevice;
}

ALCcontext *	Sound::getContext() const {
	return (this->_context);
}

void			Sound::setContext(const ALCcontext *newContext) {
	this->_context = newContext;
}

ALCenum			Sound::getError() const {
	return (this->_error);
}

void			Sound::setError(const ALCenum newError) {
	this->_error = newError;
}

ALCenum			Sound::getFormat() const {
	return (this->_format);
}

void			Sound::setFormat(const ALCenum newFormat) {
	this->_format = newFormat;
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

void			Sound::checkForErrors() {
	this->_error = alGetError();
	if (this->_error != AL_NO_ERROR)
	{
		std::cout << "Sound encountered an error: " << alutGetErrorString() << std::endl;
		throw (Exceptions::SoundGeneralError(static_cast<int>this->_error));
	}
}

void			Sound::startBackgroundMusic() {
	WAVFile backgroundMusic = WAVFile("../resources/sounds/DeathWave.wav");
	this->frequency = backgroundMusic.getSampleRate();
	alGenBuffers((ALuint)1, &this->_musicBuffer);
	alGenSources((ALuint)1, &this->_musicSource);
	
	checkForErrors();
	alSourcef(source, AL_PITCH, 1);
	checkForErrors();
	alSourcef(source, AL_GAIN, 1);
	checkForErrors();
	alSource3f(source, AL_POSITION, 0, 0, 0);
	checkForErrors();
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	checkForErrors();
	alSourcei(source, AL_LOOPING, AL_FALSE);
	checkForErrors();
}

int			Sound::checkWAVFile(FILE *fp) {

}