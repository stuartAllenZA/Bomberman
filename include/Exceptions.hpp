#ifndef INCLUDE_EXCEPTIONS_CLASS_HPP_
#define INCLUDE_EXCEPTIONS_CLASS_HPP_

#include <stdexcept>
#include <string>

class Exceptions {
	public:
		class UndefinedObject: public std::exception {
			public:
				virtual const char*	what() const throw() {
					return "Shared object does not exist.";
				}
		};

		class UndefinedSymbol: public std::exception {
			public:
				virtual const char*	what() const throw() {
					return "Method does not exist in external library.";
				}
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

		class EmptyUnameData: public std::exception {
			public:
				virtual const char*	what() const throw() {
					return "Unable to generate libray name. Function call to 'uname()' returned -1.";
				}
		};
};

#endif
