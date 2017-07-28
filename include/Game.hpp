#ifndef INCLUDE_GAME_HPP
#define INCLUDE_GAME_HPP

#include <string>
#include <iostream>
#include <Exceptions.hpp>
#include <Character.hpp>
#include <Settings.hpp>
#include <Player.hpp>

class Game {
	public:
		Game();
		Game(Game const & src);
		~Game();
		Game & 	operator=(Game const & src);
		bool	getExit() const;
		void	setExit(const bool newExit);
		int		getGameInput() const;
		void	setGameInput(const int newInput);

		void	loadStuff();

	private:
		bool					_exit;
		int						_gameInput;
		Settings				_settings;
		Character				_player;
		std::vector<Character>	_enemies;
};

#endif
