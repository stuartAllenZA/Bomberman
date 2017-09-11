#ifndef WAVFILE_HPP
#define WAVFILE_HPP

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <OpenAL/al.h>

/*
 * 
 * Wave (*.wav) PCM File Format
 * 
 * OFFSET  SIZE  NAME             DESCRIPTION
 * 0         4   ChunkID          Contains the letters "RIFF"
 * 4         4   ChunkSize        38 + ExtraParamSize + SubChunk2Size
 *                                This is the offset of the actual sound data
 * 8         4   Format           Contains the letters "WAVE"
 * 12        4   Subchunk1ID      Contains the letters "fmt "
 * 16        4   Subchunk1Size    18 + ExtraParamSize
 * 20        2   AudioFormat      PCM = 1 (i.e. Linear quantization)
 * 22        2   NumChannels      mono = 1, stereo = 2, etc.
 * 24        4   SampleRate       8000, 44100, etc.
 * 28        4   ByteRate         == SampleRate * NumChannels * BitsPerSample/8
 * 32        2   BlockAlign       == NumChannels * BitsPerSample/8
 * 34        2   BitsPerSample    8 bits = 8, 16 bits = 16, etc.
 * 36        4   Subchunk2ID      Contains the letters "data"
 * 40        4   Subchunk2Size    == NumSamples * NumChannels * BitsPerSample/8
 *                                the number of data bytes
 * 44        *   Data             the actual sound data.
 * 
 */

class WAVFile {
public:
	WAVFile(std::string path);
	~WAVFile();
	WAVFile(WAVFile const & src);
	WAVFile &		operator=(WAVFile const &src);
	std::string		getPath() const;
	void			setPath(const std::string newPath);
	std::fstream	getFS() const;
	void			setFS(const std::fstream newFS);
	char			getType(const int index) const;
	void			setType(const int index, const char newValue);
	unsigned char	*getData() const;
	void			setData(const unsigned char *newData, const unsigned long newDataSize);
	unsigned short	getFormatType() const;
	void			setFormatType(const unsigned short newFormatType);
	unsigned short	getChannels() const;
	void			setChannels(const unsigned short newChannels);
	unsigned short	getBitsPerSample() const;
	void			setBitsPerSample(const unsigned short newBytesPerSample);
	unsigned short	getBytesPerSample() const;
	void			setBytesPerSample(const unsigned short newBytesPerSample);
	unsigned long	getSize() const;
	void			setSize(const unsigned long newSize);
	unsigned long	getSubChunk1Size() const;
	void			setSubChunk1Size(const unsigned long newSubChunk1Size);
	unsigned long	getSampleRate() const;
	void			setSampleRate(const unsigned long newSampleRate);
	unsigned long	getAvgBytesPerSec() const;
	void			setAvgBytesPerSec(const unsigned long newAvgBytesPerSec);
	unsigned long	getDataSize() const;
	void			setDataSize(const unsigned long newDataSize);
	int				getSamples() const;
	void			setSamples(const int newSamples);
	bool			getValid() const;
	void			setValid(const bool newValid);
	ALenum			getFormat() const;
	void			setFormat(const ALenum newFormat);
	void			printInvalidError(const std::string& error);
	void			printValidError(const std::string& error);
	void			initWAVFile();
	void			flipBytes(const unsigned short num);
	void			flipBytes(const unsigned long num);

private:
	std::string		_path;
	std::fstream	_fs;
	unsigned char	*_data;
	unsigned short	_formatType;
	unsigned short	_channels;
	unsigned short	_bitsPerSample;
	unsigned short	_bytesPerSample;
	unsigned long	_size;
	unsigned long	_subChunk1Size;
	unsigned long	_sampleRate;
	unsigned long	_avgBytesPerSec;
	unsigned long	_dataSize;
	int				_samples;
	bool			_valid;
	ALenum			_format;
};

std::ostream &		operator<<(std::ostream & o, WAVFile const & rhs);

#endif
