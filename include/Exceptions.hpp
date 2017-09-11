#ifndef INCLUDE_EXCEPTIONS_CLASS_HPP_
#define INCLUDE_EXCEPTIONS_CLASS_HPP_

#include <stdexcept>
#include <string>

class Exceptions {
	public:
		class SoundDeviceInitError: public std::exception {
			public:
				virtual const char*	what() const throw() {
					return "Sound was unable to create a device.";
				}
		};

		class SoundContextInitError: public std::exception {
			public:
				virtual const char*	what() const throw() {
					return "Sound was unable to make the context current.";
				}
		};

		class SoundGeneralError: public std::exception {
			public:
				SoundGeneralError(const int code, const std::string & error) throw();
				~SoundGeneralError() throw();
				virtual const char*	what() const throw();
			private:
				std::string _msg;
		};

		class LexOpenFileError: public std::exception {
			public:
				LexOpenFileError(std::string const & fileName) throw();
				~LexOpenFileError() throw();
				virtual const char*	what() const throw();
			private:
				std::string _msg;
		};

		class LexFormatError: public std::exception {
			public:
				LexFormatError(int const & num, std::string const & line) throw();
				~LexFormatError() throw();
				virtual const char*	what() const throw();			
			private:
				std::string _msg;
		};

		class LexKeyNotFound: public std::exception {
			public:
				LexKeyNotFound(std::string const & key) throw();
				~LexKeyNotFound() throw();
				virtual const char*	what() const throw();
			private:
				std::string _msg;
		};
};

#endif
