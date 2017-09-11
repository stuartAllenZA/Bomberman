void			WAVFile::initWAVFile() {
	//init types array to null
	for (int i = 0; i < 4; i++)
		this->_type[i] = '\0';
	std::cout << "Checking path validity\n";
	checkPath();
	//Open the file & read the ChunkID, which should be the characters "RIFF"
	if (this->_valid) {
		std::cout << "Open the file & Check for 'RIFF'\n";
		this->_fp = fopen(this->_path.c_str(), "rb");
		fread(this->_type, sizeof(char), 4, this->_fp);
		if (this->_type[0] != 'R' || this->_type[1] != 'I' || this->_type[2] != 'F' || this->_type[3] != 'F')
			printInvalidError("Not RIFF: " + this->_path);
	}
	if (this->_valid) {
		fread(&this->_size, sizeof(unsigned long), 1, this->_fp);
		fread(this->_type, sizeof(char), 4, this->_fp);
		//Check for 'WAVE' and/or 'fmt '
		std::cout << "Check for 'WAVE'\n";
		
		if (this->_type[0] != 'W' || this->_type[1] != 'A' || this->_type[2] != 'V' || this->_type[3] != 'E')
			printValidError("Not WAVE: " + this->_path);
		else
		{
			fread(this->_type, sizeof(char), 4, this->_fp);
			std::cout << "'WAVE' check passed.\n";
		}
		//Check for 'fmt '
		std::cout << "Check for 'fmt '.\n";
		if (this->_type[0] != 'f' || this->_type[1] != 'm' || this->_type[2] != 't' || this->_type[3] != ' ')
			printInvalidError("Not 'fmt ': " + this->_path);
		else
			std::cout << "'fmt ' check passed.\n";
	}
	//Read info into vars & check if data is present
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
	//Determine AL format, read file size, allocate memory & read data
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
		fread(&this->_dataSize, sizeof(unsigned long), 1, this->_fp);
		this->_data = new unsigned char[this->_dataSize];
		fread(this->_data, sizeof(BYTE), this->_dataSize, this->_fp);
		std::cout << "WAVFile Sucsessfully Initialized\n";
	}
}