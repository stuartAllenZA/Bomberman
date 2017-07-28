#ifndef INCLUDE_GAME_CLASS_HPP_
#define INCLUDE_GAME_CLASS_HPP_

#include <string>
#include <GraphicsHandler.hpp>
#include <Exceptions.hpp>

class Game {
	public:
		Game();
		~Game();
		void	run();
		void	setGameInput();
		int		getGameInput();

	private:
		int		gameInput;
};

#endif

