#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include "Exceptions.hpp"
#include "Character.hpp"
#include "Settings.hpp"
#include "Player.hpp"
#include "Sound.hpp"
#include "Box.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <string>
#include <irrKlang.h>
#include <dirent.h>

// Add variable checklist

//		1. Getter & Setter
//		2. Add to << operator overload
//		3. Add to = operator overload
//		4. Check if it can be default constructed, if so, add

enum class GameState {
	MENU,
	PLAY,
	LOAD,
	SET,
	SAVE,
	EXIT
};

enum class PlayState {
	PLAYER_SELECT,
	GAME_LOAD,
	GAME_PLAY
};

class Game {
	public:
		Game();
		Game(Game const & src);
		~Game();
		Game & 					operator=(Game const & src);
		GameState				getGameState() const;
		void					setGameState(const GameState newState);
		PlayState				getPlayState() const;
		void					setPlayState(const PlayState newState);
		int						getGameInput() const;
		void					setGameInput(const int newInput);
		Settings				getSettings() const;
		void					setSettings(const Settings newSettings);
		Player					getPlayer() const;
		void					setPlayer(const Player newPlayer);
		Sound				&	getSound();
		void					setSound(const Sound newSound);
		std::vector<Character*>	getEnemies() const;
		void					setEnemies(const std::vector<Character*> newEnemies);
		bool 					getHasSave() const;
		void 					setHasSave(const bool newHasSave);

		void					initSound();
		void					saveSettings();
		void					savePlayer();
		void					saveGame();
		std::vector<char *>		checkPlayers();
		void					loadPlayer(std::string playerName);
		void					loadGame();
		void					loadSettings();
		std::string				lexFile(std::string fileName, std::string find);
		void					startBackgroundMusic();
		void					stopBackgroundMusic();

	private:
		GameState				_gameState;
		PlayState				_playState;
		int						_gameInput;
		Settings				_settings;
		Sound					_sound;
		Player					_player;
		std::vector<Character*>	_enemies;
		bool					_hasSave;
};

std::ostream &					operator<<(std::ostream & o, Game const & rhs);

#endif
