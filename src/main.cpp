#include <header.hpp>

int main(int argc, char **argv) {
	//Check for start arguments
	if (argc > 1) {
		std::cout << "Argument has been passed.\n";
		if (strcmp(argv[1], "--help"))
			std::cout << "Please run Bomberman without any arguments as all configs are done in game.\n";
	}

	try {
		Core core;
		// Spawn player
		// Spawn u-box
		// Spawn box0 - empty
		// Spawn box1 - enemy
		// Spawn box2 - upgrade
		// Spawn box3 - hatch
		// Move player
		// Place bomb
		// move player
		// detonate bomb
		// destroy box
		// Move player
		// Place bomb
		// move player
		// explode bomb
		// destroy box
		// drop enemy
		// move player
		// move enemy
		// place bomb
		// move player
		// move enemy
		// detonate bomb
		// kill enemy
		// xp up player
		// move player
		// place bomb
		// move player
		// detonate bomb
		// destroy box
		// drop upgrade
		// move player
		// collect upgrade
		// activate upgrade on player
		// move player
		// place bomb
		// move player
		// detonate bomb
		// destroy box
		// drop hatch
		// move player
		// finish demo
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
