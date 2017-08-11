#include <header.hpp>

int main(int argc, char **argv) {
	//Check for start arguments
	if (argc > 1) {
		std::cout << "Argument has been passed.\n";
		if (strcmp(argv[1], "--help"))
			std::cout << "Please run Bomberman without any arguments as all configs are done in game.\n";
	}

	try {
		//Generate Library Name
		struct utsname unameData;
		if (uname(&unameData) == -1)
			throw (Exceptions::EmptyUnameData());
		std::stringstream ss;
		ss << "libopengl_" << unameData.machine << "_" << unameData.sysname << ".so";
		std::string libname = ss.str();

		//Construct Objects & declare vars
		std::cout << "Constructing Game\n";
		Game				game;
		std::cout << "Constructing Graphics\n";
		GraphicsHandler		graphics(libname);
		std::string line;

		//Dump status of Game
		std::cout << game << std::endl;
		
		//Init grapics & start loop
		// graphics.init();
		while (game.getExit() == false) {
			std::getline(std::cin, line);
			if (line == "exit" || line == "q")
				game.setExit(true);
			// game.setGameInput(graphics.getUserInput());
			// game.updateGameData();
			// graphics.loadGameToRenderBuff(game);	
			// graphics.render();
		}
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
