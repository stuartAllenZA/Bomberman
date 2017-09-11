void FileIO::readBigEndian(ushort& aNumber) {
   this->read((char*)&aNumber, sizeof(aNumber));
   aNumber = flipBytes(aNumber);
}

void FileIO::readBigEndian(ulong& aNumber) {
   this->read((char*)&aNumber, sizeof(aNumber));
   aNumber = flipBytes(aNumber);
}

void FileIO::readLittleEndian(ushort& aNumber) {
   this->read((char*)&aNumber, sizeof(aNumber));
}

void FileIO::readLittleEndian(ulong& aNumber) {
   this->read((char*)&aNumber, sizeof(aNumber));
}



void SoundHeader::processInWavFormat(const char *filename) {

   FileIO sndfile;

   sndfile.open(filename, ios::in);
   if (!sndfile.is_open()) {
      cerr << "Error: sound file " << filename
      << " could not be opened!" << endl;
      exit(1);
   }
   ulong tempLong;
   ushort tempShort;

   // read the ChunkID, which should be the characters "RIFF":
   sndfile.readBigEndian(tempLong);
   if (tempLong != 0x52494646) {
      cerr << "Error: ChunkID expected to be 0x52494646 (RIFF), but is: "
      << hex << tempLong << endl;
      exit(1);
   }


   // read the ChunkSize (ignore for Canonical WAVE format):
   sndfile.readLittleEndian(tempLong);

   
   // read the Format:
   sndfile.readBigEndian(tempLong);
   if (tempLong != 0x57415645) {
      cerr << "Error: expecting the WAVE format (0x57415645 = WAVE) \n"
      << "   but got: " << tempLong << endl;
      exit(1);
   }


   // read the Subchunk1ID (should be "fmt "):
   sndfile.readBigEndian(tempLong);
   if (tempLong != 0x666d7420) {
      cerr << "Error: expecting the fmt subchunk (0x666d7420) \n"
      << "   but got: " << tempLong << endl;
      exit(1);
   }


   // read the Subchunk1Size:
   sndfile.readLittleEndian(tempLong);
   if (tempLong != 16) {
      cerr << "Error: expecting the fmt subchunk size to be 16, \n"
      << "   but it is: " << tempLong << endl;
      exit(1);
   }


   // read the AudioFormat:
   sndfile.readLittleEndian(tempShort);
   if (tempShort != 1) {
      cerr << "Error: expecting audio format to be PCM (1). " << endl
      << "   Cannot handle this format (compression): " 
      << tempShort << endl;
      exit(1);
   }


   // read the NumChannels:
   sndfile.readLittleEndian(tempShort);
   if (tempShort > 1000) {
      cerr << "Error: I don't believe this file has " << tempShort 
      << " channels" << endl;
      exit(1);
   }
   channels = tempShort;


   // read the SampleRate:
   sndfile.readLittleEndian(tempLong);
   samplingRate = tempLong;


   // read the ByteRate == SampleRate * NumChannels * BitsPerSample/8:
   sndfile.readLittleEndian(tempLong);


   // read the BlockAlign == NumChannels * BitsPerSample/8:
   sndfile.readLittleEndian(tempShort);


   // read the BitsPerSample:
   sndfile.readLittleEndian(tempShort);
   bitsPerSample = tempShort;


   // read the Subchunk2ID (should be "data" (0x64617461)):
   sndfile.readBigEndian(tempLong);


   // read the Subchunk2Size, calculate the number of samples:
   sndfile.readLittleEndian(tempLong);
   samples = tempLong / (bitsPerSample/8) / channels;

   sndfile.close();

   // process data elements of SoundHeader

   // dataLocation = 44;

   // channels already set
   // samplingRate already set
   // sample count already set
   // bits per sample already set
   
   // inputType already set before entering function but set again just in case:
   inputType = TYPE_WAV_PCM;
   outputType = inputType;

   // set the comment string to nothing:
   if (commentString != NULL) {
      delete [] commentString;
   }
   commentString = new char[1];
   commentString[0] = '\0';
   commentLength = 0;

   // set the Next_DataFormat
   guessNextFormat();

   updateDerivedVariables();
}



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




//////////////////////////////
//
// SoundHeader::updateDerivedVariables
//

void SoundHeader::updateDerivedVariables(void) {
   blockAlign = getBitsPerSample()/8 * getChannels();
   sampleBytes = getBitsPerSample() / 8;

};