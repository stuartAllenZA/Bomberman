#ifndef SOUND_HPP
#define SOUND_HPP

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <OpenAL/alc.h>
#include <OpenAL/al.h>
#include "WAVFile.hpp"
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
	ALenum		getError() const;
	void		setError(const ALenum newError);
	ALuint		getMusicSource() const;
	void		setMusicSource(const ALuint newMusicSource);
	ALuint		getMusicBuffer() const;
	void		setMusicBuffer(const ALuint newMusicBuffer);
	ALfloat		getSourcePos(const int index) const;
	void		setSourcePos(const int index, const float newValue);
	ALfloat		getSourceVel(const int index) const;
	void		setSourceVel(const int index, const float newValue);
	ALfloat		getListenerPos(const int index) const;
	void		setListenerPos(const int index, const float newValue);
	ALfloat		getListenerVel(const int index) const;
	void		setListenerVel(const int index, const float newValue);
	ALfloat		getListenerOri(const int index) const;
	void		setListenerOri(const int index, const float newValue);
	int			getMusicVol() const;
	void		setMusicVol(const int newVol);
	int			getFXVol() const;
	void		setFXVol(const int newVol);
	void		checkForErrors();
	void		startBackgroundMusic();
	//void		processMusicVolume();
	void		initSound();

private:
	ALCdevice	*_device;
	ALCcontext	*_context;
	ALenum		_error;
	ALuint		_musicSource;
	ALuint		_musicBuffer;
	ALfloat		_sourcePos[3];
	ALfloat		_sourceVel[3];
	ALfloat		_listenerPos[3];
	ALfloat		_listenerVel[3];
	ALfloat		_listenerOri[6];
	int			_musicVol;
	int			_FXVol;
};

#endif
