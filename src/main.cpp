#include <Window.hpp>
#include <Exceptions.hpp>

int main(int argc, char **argv) {
	//Check for start arguments
	if (argc > 1) {
		std::cout << "Argument has been passed.\n";
		if (strcmp(argv[1], "--help"))
			std::cout << "Please run Bomberman without any arguments as all configs are done in game.\n";
	}

	try {
		Window window;
	}

	//Catch Fatal Exceptions
	catch (Exceptions::UndefinedObject const & exception) {
		std::cerr << "undefined object exception: " << exception.what() << std::endl;
	}

	catch (Exceptions::UndefinedSymbol const & exception) {
		std::cerr << "undefined symbol exception: " << exception.what() << std::endl;
	}

	catch (Exceptions::LexOpenFileError const & exception) {
		std::cerr << "Exceptions::LexOpenFileError: " << exception.what() << std::endl;
	}

	catch (Exceptions::LexFormatError const & exception) {
		std::cerr << "Exceptions::LexFormatError: " << exception.what() << std::endl;
	}

	catch (Exceptions::LexKeyNotFound const & exception) {
		std::cerr << "Exceptions::LexKeyNotFound: " << exception.what() << std::endl;
	}

	catch (Exceptions::EmptyUnameData const & exception) {
		std::cerr << "Exceptions::EmptyUnameData: " << exception.what() << std::endl;
	}

	catch (std::exception const & exception) {
		std::cerr << "std::exception: " << exception.what() << std::endl;
	}

	catch (...) {
		std::cerr << "unknown exception: " << std::endl;
	}

	return (0);
}
