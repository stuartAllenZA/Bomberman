#include <WAVFile.hpp>

WAVFile::WAVFile(std::string path) : _path(path), _fp(nullptr), _data(nullptr), _valid(true) {
	std::cout << "WAVFile " << this->_path << " Sucsessfully Constructed\n";
}

WAVFile::WAVFile(WAVFile const & src) {
	std::cout << "WAVFile Copy-Constructed\n";
	*this = src;
}

WAVFile::~WAVFile() {
	if (this->_valid == true) {
		fclose(this->_fp);
		delete[] this->_data;
	}
	std::cout << "WAVFile De-Constructed\n";
}

WAVFile &		WAVFile::operator=(WAVFile const &src) {
	this->_path = src.getPath();
	this->_fp = src.getFP();
	this->_type[0] = src.getType(0);
	this->_type[1] = src.getType(1);
	this->_type[2] = src.getType(2);
	this->_type[3] = src.getType(3);
	this->_data = src.getData();
	this->_formatType = src.getFormatType();
	this->_channels = src.getChannels();
	this->_bitsPerSample = src.getBitsPerSample();
	this->_bytesPerSample = src.getBytesPerSample();
	this->_size = src.getSize();
	this->_chunkSize = src.getChunkSize();
	this->_sampleRate = src.getSampleRate();
	this->_avgBytesPerSec = src.getAvgBytesPerSec();
	this->_dataSize = src.getDataSize();
	this->_valid = src.getValid();
	this->_format = src.getFormat();
	return (*this);
}

std::string		WAVFile::getPath() const {
	return (this->_path);
}

void			WAVFile::setPath(const std::string newPath) {
	this->_path = newPath;
}

FILE		*	WAVFile::getFP() const {
	return (this->_fp);
}

void			WAVFile::setFP(FILE *newFP) {
	this->_fp = (FILE*)malloc(sizeof(FILE));
	this->_fp = (FILE*)memcpy(this->_fp, newFP, sizeof(FILE));
}

char			WAVFile::getType(const int index) const {
	return (this->_type[index]);
}

void			WAVFile::setType(const int index, const char newValue) {
	this->_type[index] = newValue;
}

unsigned char*	WAVFile::getData() const {
	return (this->_data);
}

void			WAVFile::setData(const unsigned char *newData, const unsigned long newDataSize) {
	this->_data = (unsigned char*)malloc(sizeof(unsigned char*) * newDataSize);
	this->_dataSize = newDataSize;
	this->_data = (unsigned char*)memcpy(this->_data, newData, this->_dataSize);
}

unsigned short	WAVFile::getFormatType() const {
	return (this->_formatType);
}

void			WAVFile::setFormatType(const unsigned short newFormatType) {
	this->_formatType = newFormatType;
}

unsigned short	WAVFile::getChannels() const {
	return (this->_channels);
}

void			WAVFile::setChannels(const unsigned short newChannels) {
	this->_channels = newChannels;
}

unsigned short	WAVFile::getBitsPerSample() const {
	return (this->_bitsPerSample);
}

void			WAVFile::setBitsPerSample(const unsigned short newBitsPerSample) {
	this->_bitsPerSample = newBitsPerSample;
}

unsigned short	WAVFile::getBytesPerSample() const {
	return (this->_bytesPerSample);
}

void			WAVFile::setBytesPerSample(const unsigned short newBytesPerSample) {
	this->_bytesPerSample = newBytesPerSample;
}

unsigned long	WAVFile::getSize() const {
	return (this->_size);
}

void			WAVFile::setSize(const unsigned long newSize) {
	this->_size = newSize;
}

unsigned long	WAVFile::getSubChunk1Size() const { 
	return (this->_subChunk1Size);
}

void			WAVFile::setSubChunk1Size(const unsigned long newSubChunk1Size) {
	this->_subChunk1Size = newSubChunk1Size;
}

unsigned long	WAVFile::getSampleRate() const {
	return (this->_sampleRate);
}

void			WAVFile::setSampleRate(const unsigned long newSampleRate) {
	this->_sampleRate = newSampleRate;
}

unsigned long	WAVFile::getAvgBytesPerSec() const {
	return (this->_avgBytesPerSec);
}

void			WAVFile::setAvgBytesPerSec(const unsigned long newAvgBytesPerSec) {
	this->_avgBytesPerSec = newAvgBytesPerSec;
}

unsigned long	WAVFile::getDataSize() const {
	return (this->_dataSize);
}

void			WAVFile::setDataSize(const unsigned long newDataSize) {
	this->_dataSize = newDataSize;
}
int				WAVFile::getSamples() const {
	return (this->_samples);
}

void			WAVFile::setSamples(const int newSamples) {
	this->_samples = newSamples;
}

bool			WAVFile::getValid() const {
	return (this->_valid);
}

void			WAVFile::setValid(const bool newValid) {
	this->_valid = newValid;
}

ALenum			WAVFile::getFormat() const {
	return (this->_format);
}

void			WAVFile::setFormat(const ALenum newFormat) {
	this->_format = newFormat;
}

void			WAVFile::printInvalidError(const std::string& error) {
	this->_valid = false;
	std::cerr << "WAVFile encountered an invalid error: " << error << std::endl;
}

void			WAVFile::printValidError(const std::string& error) {
	std::cerr << "WAVFile encountered an valid error: " << error << std::endl;
}

void			WAVFile::initWAVFile() {
	unsigned long tempLong;
	unsigned short tempShort;

	this->_fs.open(this->_path, ios::in);
	if (!this->_fs.is_open())
		printInvalidError("Unable to open WAV File: " + this->_path);
	// read the ChunkID, which should be the characters "RIFF"
	this->_fs.read((char*)&tempLong, sizeof(tempLong));
	tempLong = flipBytes(tempLong);
	if (tempLong != 0x52494646)
		printInvalidError("Not 'RIFF': " + this->_path);
	// read the ChunkSize (ignore for Canonical WAVE format)
	this->_fs.read((char*)&tempLong, sizeof(tempLong));
	// read the Format
	this->_fs.read((char*)&tempLong, sizeof(tempLong));
	tempLong = flipBytes(tempLong);
	if (tempLong != 0x57415645)
		printInvalidError("Not 'WAVE': " + this->_path);
	// read the Subchunk1ID (should be "fmt ")
	this->_fs.read((char*)&tempLong, sizeof(tempLong));
	tempLong = flipBytes(tempLong);
	if (tempLong != 0x666d7420)
		printInvalidError("Not 'fmt ': " + this->_path);
	// read the Subchunk1Size
	this->_fs.read((char*)&this->_subChunk1Size, sizeof(tempLong));
	if (this->_subChunk1Size != 16)
		printInvalidError("Bad SubChunk1Size: " + this->_path);
	// read the AudioFormat
	this->_fs.read((char*)&this->_formatType, sizeof(tempShort));
	if (this->_formatType != 1)
		printInvalidError("Expecting audio format to be PCM. File " + this->_path + " is compressed.");
	// read the NumChannels
	this->_fs.read((char*)&this->_channels, sizeof(tempShort));
	if (this->_channels > 1000)
		printInvalidError("File " + this->_path + " has " + this->_channels + " channels.");
	// read the SampleRate
	this->_fs.read((char*)&this->_sampleRate, sizeof(tempLong));
	// read the ByteRate == SampleRate * NumChannels * BitsPerSample/8
	this->_fs.read((char*)&this->_avgBytesPerSec, sizeof(tempLong));
	// read the BlockAlign == NumChannels * BitsPerSample/8
	this->_fs.read((char*)&this->_bytesPerSample, sizeof(tempShort));
	// read the BitsPerSample
	this->_fs.read((char*)&this->_bitsPerSample, sizeof(tempShort));
	// read the Subchunk2ID (should be "data" (0x64617461))
	this->_fs.read((char*)&tempLong, sizeof(tempLong));
	tempLong = flipBytes(tempLong);
	if (tempLong != 0x64617461)
		printInvalidError("Not data: " + this->_path);
	// read the Subchunk2Size, calculate the number of samples
	this->_fs.read((char*)&this->_dataSize, sizeof(tempLong));
	this->_samples = this->_dataSize / (this->bytesPerSample) / channels;
	if (this->_valid) {
		std::cout << "Determine AL format, read file size, allocate memory & read data\n";
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
		fread(this->_data, sizeof(BYTE), this->_dataSize, this->_fp);
		std::cout << "WAVFile Sucsessfully Initialized\n";
	}
}

if (this->_valid) {
		std::cout << "Read info into vars & check if data is present\n";
		fread(&this->_chunkSize, sizeof(unsigned long), 1, this->_fp);
		fread(&this->_formatType, sizeof(unsigned short), 1, this->_fp);
		fread(&this->_channels, sizeof(unsigned short), 1, this->_fp);
		fread(&this->_sampleRate, sizeof(unsigned long), 1, this->_fp);
		fread(&this->_avgBytesPerSec, sizeof(unsigned long), 1, this->_fp);
		fread(&this->_bytesPerSample, sizeof(unsigned short), 1, this->_fp);
		fread(&this->_bitsPerSample, sizeof(unsigned short), 1, this->_fp);
		fread(this->_type, sizeof(char), 4, this->_fp);
		if (this->_type[0] != 'd' || this->_type[1] != 'a' || this->_type[0] != 't' || this->_type[0] != 'a')
			printInvalidError("Missing data: " + this->_path);
	}
	fread(&this->_dataSize, sizeof(unsigned long), 1, this->_fp);


unsigned short	WAVFile::flipBytes(unsigned short num) {
   static uchar output[2];
   static uchar* input;
   input = (uchar*)(&num);

   output[0] = input[1];
   output[1] = input[0];

   return *((unsigned short*)(&output));
}

unsigned long	WAVFile::flipBytes(unsigned long num) {
   static uchar output[4];
   static uchar* input;
   input = (uchar*)(&num);

   output[0] = input[3];
   output[1] = input[2];
   output[2] = input[1];
   output[3] = input[0];

   return *((unsigned long*)(&output));
}

std::ostream & 	operator<<(std::ostream & o, WAVFile const & rhs) {
	int i;

	o << "Dumping WAVFile" << "\nPath: " << rhs.getPath() << std::endl;
	for (i = 0; i < 4; i++) {
		o << "Type[" << i << "]: " << rhs.getType(i) << std::endl;
	}
	o << "Format Type: " << rhs.getFormatType() <<
	"\nChannels: " << rhs.getChannels() <<
	"\nBits Per Sample: " << rhs.getBitsPerSample() <<
	"\nBytes Per Sample: " << rhs.getBytesPerSample() <<
	"\nSize: " << rhs.getSize() <<
	"\nChunk Size: " << rhs.getChunkSize() <<
	"\nSample Rate: " << rhs.getSampleRate() <<
	"\nAvg Bytes Per Second: " << rhs.getAvgBytesPerSec() <<
	"\nData Size: " << rhs.getDataSize() <<
	"\nValid: " << rhs.getValid() <<
	"\nFormat: " << rhs.getFormat() << std::endl;

	//static_cast<std::underlying_type<GameState>::type>(rhs.getGameState()) <<
	return o;
}
