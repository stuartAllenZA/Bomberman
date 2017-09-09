#include <WAVFile.hpp>

WAVFile::WAVFile(std::string path) : _path(path), _fp(nullptr), _valid(true) {
	if (checkPath())
		initWAVFile();
	if (this->_valid)
		std::cout << "WAVFile " << this->path << " Sucsessfully Constructed\n";
	else
		std::cout << "WAVFile " << this->path << " Unsucsessfully Constructed\n";
}

WAVFile::WAVFile(WAVFile const & src) {
	std::cout << "WAVFile Copy-Constructed\n";
	*this = src;
}

WAVFile::~WAVFile() {
	if (this->_valid = true) {
		fclose(this->_fp);
	}
	std::cout << "WAVFile De-Constructed\n";
}

bool		WAVFile::checkPath() {
	struct stat buffer;

	stat(this->_path.c_str(), &buffer);
	if (!buffer) {
		printError("Unable to open WAV File: " + this->path);
		return (false);
	}
	else
		return (true);
}

void	WAVFile::printError(const std::string& error) {
	this->_valid = false;
	std::cout << "WAVFile encountered an error: " << error << std::endl;
}

void	WAVFile::initWAVFile() {
	//Open the file
	this->_fp = fopen(this->path);
	//Check for 'RIFF'
	fread(this->_type, sizeof(char), 4, this->_fp);
	if (this->_type[0] != 'R' || this->_type[1] != 'I' || this->_type[0] != 'F' || this->_type[0] != 'F')
		printError("Not RIFF: " + this->path);
	//Check for 'WAVE'
	if (this->_valid) {
		fread(&this->_Size, sizeof(DWORD), 1, this->_fp);
		fread(this->_type, sizeof(char), 4, this->_fp);
		if (this->_type[0] != 'W' || this->_type[1] != 'A' || this->_type[0] != 'V' || this->_type[0] != 'E')
			printError("Not WAVE: " + this->path);
	}
	//Check for 'fmt '
	if (this->_valid) {
		fread(this->_type, sizeof(char), 4, this->_fp);
		if (this->_type[0] != 'f' || this->_type[1] != 'm' || this->_type[0] != 't' || this->_type[0] != ' ')
			printError("Not WAVE: " + this->path);
	}
	//Read info into vars & check if data is present
	if (this->_valid) {
		fread(&this->_chunkSize, sizeof(DWORD), 1, this->_fp);
		fread(&this->_formatType, sizeof(short), 1, this->_fp);
		fread(&this->_channels, sizeof(short), 1, this->_fp);
		fread(&this->_sampleRate, sizeof(DWORD), 1, this->_fp);
		fread(&this->_avgBytesPerSec, sizeof(DWORD), 1, this->_fp);
		fread(&this->_bytesPerSample, sizeof(short), 1, this->_fp);
		fread(&this->_bitsPerSample, sizeof(short), 1, this->_fp);
		fread(this->_type, sizeof(char), 4, this->_fp);
		if (this->_type[0] != 'd' || this->_type[1] != 'a' || this->_type[0] != 't' || this->_type[0] != 'a')
			printError("Missing data: " + this->path);
	}
	//Determine AL format, read file size, allocate memory & read data
	if (this->_valid) {
		if(this->_bitsPerSample == 8)
		{
			if(this->_channels == 1)
				this->_format = AL_FORMAT_MONO8;
			else if(this->_channels == 2)
				this->_format = AL_FORMAT_STEREO8;
		}
		else if(this->_bitsPerSample == 16)
		{
			if(this->_channels == 1)
				this->_format = AL_FORMAT_MONO16;
			else if(this->_channels == 2)
				this->_format = AL_FORMAT_STEREO16;
		}
		fread(&this->_dataSize, sizeof(DWORD), 1, this->_fp);
		this->_data = new unsigned char[this->_dataSize];
		fread(this->_data, sizeof(BYTE), this->_dataSize, this->_fp);
	}
}

DWORD	WAVFile::getSampleRate() const {
	return (this->_sampleRate);
}

ALCenum	WAVFile::getFormat() const {
	return (this->_format);
}

void	WAVFile::setFormat(const ALCenum newFormat) {
	this->_format = newFormat;
}