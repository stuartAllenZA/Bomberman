#ifndef WAVFILE_HPP
#define WAVFILE_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <AL/al.h>

class WAVFile {
public:
	WAVFile(std::string path);
	~WAVFile();
	WAVFile(WAVFile const & src);
	WAVFile &		operator=(WAVFile const &src);
	bool			checkPath();
	void			printError(const std::string& error);
	DWORD			getSampleRate() const;
	ALCenum			getFormat() const;
	void			setFormat(const ALCenum newFormat);

private:
	std::string		_path;
	FILE			*_fp;
	char			_type[4];
	unsigned char	*_data;
	short			_formatType;
	short			_channels;
	short			_bitsPerSample;
	short			_bytesPerSample;
	DWORD			_size;
	DWORD			_chunkSize;
	DWORD			_sampleRate;
	DWORD			_avgBytesPerSec;
	DWORD			_dataSize;
	bool			_valid;
	ALenum			_format;
};

#endif
