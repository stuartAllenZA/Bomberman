#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include <Exceptions.hpp>
#include <Enemy.hpp>
#include <Settings.hpp>
#include <Player.hpp>
#include <Sound.hpp>
#include <Box.hpp>
#include <Bomb.hpp>
#include <BreakableBox.hpp>
#include <UnbreakableBox.hpp>
#include <LevelHatch.hpp>
#include <RemoteDetonator.hpp>
#include <ExtraBomb.hpp>
#include <RangeExtender.hpp>
#include <EnemyDrop.hpp>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <string>
#include <irrKlang.h>
#include <dirent.h>
#include <cstdlib>
#include <ctime>

#define UP		0
#define DOWN	1
#define LEFT	2
#define RIGHT	3
#define ACTION	4
#define ACCEPT	5
#define ESCAPE	6

// Add variable checklist

//		1. Getter & Setter
//		2. Add to << operator overload
//		3. Add to = operator overload
//		4. Check if it can be default constructed, if so, add

enum class GameState {
	MENU,
	PLAY,
	EXIT
};

enum class PlayState {
	PLAYER_SELECT,
	GAME_LOAD,
	GAME_INIT,
	GAME_PLAY
};

class Game {
public:
	Game();
	Game(Game const & src);
	~Game();
	Game & 						operator=(Game const & src);
	GameState					getGameState() const;
	void						setGameState(const GameState newState);
	PlayState					getPlayState() const;
	void						setPlayState(const PlayState newState);
	bool						getKeyPressArr(const int index) const;
	void						setKeyPressArr(const int index, const bool newState);
	Settings					getSettings() const;
	void						setSettings(const Settings newSettings);
	Player						getPlayer() const;
	void						setPlayer(const Player newPlayer);
	Sound				&		getSound();
	void						setSound(const Sound newSound);
	std::vector<Enemy>			getEnemies() const;
	void						setEnemies(const std::vector<Enemy> newEnemies);
	std::vector<BreakableBox>	getBreakableBs() const;
	void						setBreakableBs(const std::vector<BreakableBox> newBreakableBs);
	std::vector<UnbreakableBox>	getUnbreakableBs() const;
	void						setUnbreakableBs(const std::vector<UnbreakableBox> newUnbreakableBs);
	std::vector<Drop*>			getDrops() const;
	void						setDrops(const std::vector<Drop*> newDrops);
	std::pair<int, int>			getMapSize() const;
	void						setMapSize(const std::pair<int, int> newMapSize);
	int							getRange() const;
	void 						setRange(const int newRange);

	void						initSound();
	void						savePlayer();
	std::vector<std::string>	checkPlayers() const;
	void						loadPlayer(const std::string playerName);
	std::string					lexFile(const std::string fileName, const std::string find);
	void						setWindowPos(const int xPos, const int yPos);
	void						updateSound();
	void						startMenuMusic();
	void						pauseMenuMusic();
	void						resumeMenuMusic();
	void						stopMenuMusic();
	void						startGameMusic();
	void						pauseGameMusic();
	void						resumeGameMusic();
	void						stopGameMusic();
	void						startCreditsMusic();
	void						pauseCreditsMusic();
	void						resumeCreditsMusic();
	void						stopCreditsMusic();
	void						setPlayerLevel(const int level);
	int							getPlayerLevel();
	void						processEnemies();
	bool						checkCoOrd(std::pair<float, float> xy);
	bool 						checkCoOrd(std::pair<float, float> xy, char *type);
	void 						controller();
	void 						moveUp();
	void 						moveDown();
	void 						moveLeft();
	void 						moveRight();
	void 						dropBomb(int *delayTimer);
	void						unbreakableRing(int x, int y);
	void						breakableRing(int x, int y);
	void						breakableRing(int x, int y, std::pair<int, int> skip);
	void						cornerBox(int x, int y);
	void						initLevelOne();
	void						initLevelTwo();
	void						initLevelThree();
	void						initTestMap();
	int							dropFreeBoxInd();
	void 						setDifficulty(const int dif);
	void						reset();

private:
	GameState					_gameState;
	PlayState					_playState;
	bool						_keyPressArr[7];
	Settings					_settings;
	Player						_player;
	Sound						_sound;
	std::vector<Enemy>			_enemies;
	std::vector<BreakableBox>	_breakableBs;
	std::vector<UnbreakableBox>	_unbreakableBs;
	std::vector<Drop*>			_drops;
	std::vector<Bomb>			_bombs;
	std::pair<int, int>			_mapSize;
	int							_range;
};

std::ostream &					operator<<(std::ostream & o, Game const & rhs);

#endif
