#ifndef INCLUDE_GAME_HPP
#define INCLUDE_GAME_HPP

#include <string>
#include <iostream>
#include <vector>
#include <Exceptions.hpp>
#include <Character.hpp>
#include <Settings.hpp>
#include <Player.hpp>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>

class Game {
	public:
		Game();
		Game(Game const & src);
		~Game();
		Game & 					operator=(Game const & src);
		bool					getExit() const;
		void					setExit(const bool newExit);
		int						getGameInput() const;
		void					setGameInput(const int newInput);
		std::vector<Character>	getEnemies() const;
		void					setEnemies(const std::vector<Character> newEnemies);
		std::string				getUsername();
		void					setUsername(std::string);
		std::string				newUser();
		void					saveGame();
		void					saveProfile();
		void					loadUserProfile();
		void					loadGame();
		void					loadSettings();

	private:
		std::string				_username;
		std::string				_profileFile;
		int						_currentLevel;
		int						_currentExp;
		bool					_exit;
		int						_gameInput;
		Settings				_settings;
		Character				_player;
		std::vector<Character>	_enemies;
};

#endif
