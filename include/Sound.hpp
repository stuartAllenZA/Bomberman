#ifndef SOUND_HPP
#define SOUND_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <AL/alc.h>
#include "WAVFile.hpp"

//	TODO:
//	1. Create member function to configure listener properties

class Sound {
public:
	Sound();
	~Sound();
	Sound(Sound const & src);
	Sound &		operator=(Sound const &src);
	ALCdevice	*getDevice() const;
	void		setDevice(const ALCdevice *newDevice);
	ALCcontext	*getContext() const;
	void		setContext(const ALCcontext *newContext);
	ALCenum		getError() const;
	void		setError(const ALCenum newError);
	ALuint		getMusicSource() const;
	void		setMusicSource(const ALuint newMusicSource);
	ALuint		getMusicBuffer() const;
	void		setMusicBuffer(const ALuint newMusicBuffer);
	void		checkForErrors();
	void		startBackgroundMusic() 

private:
	ALCdevice	*_device;
	ALCcontext	*_context;
	ALCenum		_error;
	ALCenum		_format;
	ALuint		_musicSource;
	ALuint		_musicBuffer;
	ALuint		_frequency;
};

#endif
