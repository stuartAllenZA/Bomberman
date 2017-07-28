#ifndef INCLUDE_EXCEPTIONS_CLASS_HPP_
#define INCLUDE_EXCEPTIONS_CLASS_HPP_

#include <stdexcept>

class Exceptions {
	public:
		class UndefinedObject: public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Shared object does not exist";
				}
		};

		class UndefinedSymbol: public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Method does not exist in external library";
				}
		};

};

#endif

