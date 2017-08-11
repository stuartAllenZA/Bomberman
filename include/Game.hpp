#ifndef INCLUDE_GAME_HPP
#define INCLUDE_GAME_HPP

#include <iostream>
#include <vector>
#include "Exceptions.hpp"
#include "Character.hpp"
#include "Settings.hpp"
#include "Player.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <string>

clas enum GameState
{
	PLAY,
	EXIT,
	LOAD,
	SET,
	SAVE
};

class Game {
	public:
		Game();
		Game(Game const & src);
		~Game();
		Game & 					operator=(Game const & src);
		GameState				getState() const;
		void					setState(const GameState newState);
		int						getGameInput() const;
		void					setGameInput(const int newInput);
		Settings				getSettings() const;
		void					setSettings(const Settings newSettings);
		Character				*getPlayer() const;
		void					setPlayer(Player *newPlayer);
		std::vector<Character*>	getEnemies() const;
		void					setEnemies(const std::vector<Character*> newEnemies);
		
		std::string				newUser(std::string playerName);
		void					saveGame();
		void					savePlayer();
		void					saveSettings();
		void					loadPlayer(std::string playerName);
		void					loadGame();
		void					loadSettings();
		std::string				lexFile(std::string fileName, std::string find);

		void					updateGameData();

	private:
		GameState				_state;
		int						_gameInput;
		Settings				_settings;
		Character				*_player;
		std::vector<Character*>	_enemies;
		std::vector<Box>		_unbreakableWalls;
};

std::ostream &					operator<<(std::ostream & o, Game const & rhs);

#endif
