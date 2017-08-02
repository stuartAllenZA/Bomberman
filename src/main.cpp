#include <header.hpp>

int main(int argc, char **argv) {
	if (argc > 1) {
		if (strcmp(argv[1], "--help"))
			std::cout << "Please run Bomberman without any arguments as all configs are done in game.\n";
	}

	std::string hostype(getenv("HOSTTYPE"));
	std::string libname("libopengl_" + hostype + ".so");

	try {
		Game				game;
		GraphicsHandler		graphics(libname);

		std::cout << game << std::endl;
		std::string line;
		//graphics.init();
		while (game.getExit() == false) {
			std::getline(std::cin, line);
			if (line == "exit" || line == "q")
				game.setExit(true);
			// getInput
			// updateGameState
			// render
			graphics.loadGameToRenderBuff(game);	
			graphics.render();
		}
	}

	catch (Exceptions::UndefinedObject const & exception) {
		std::cerr << "undefined object exception: " << exception.what() << std::endl;
	}

	catch (Exceptions::UndefinedSymbol const & exception) {
		std::cerr << "undefined symbol exception: " << exception.what() << std::endl;
	}

	catch (Exceptions::LexFormatError const & exception) {
		std::cerr << "Exceptions::LexFormatError: " << exception.what() << std::endl;
	}

	catch (Exceptions::LexKeyNotFound const & exception) {
		std::cerr << "Exceptions::LexKeyNotFound: " << exception.what() << std::endl;
	}

	catch (std::exception const & exception) {
		std::cerr << "std::exception: " << exception.what() << std::endl;
	}

	catch (...) {
		std::cerr << "unknown exception: " << std::endl;
	}

	return (0);
}
