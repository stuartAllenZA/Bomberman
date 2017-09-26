#include <Game.hpp>

Game::Game() : _gameState(GameState::MENU), _playState(PlayState::PLAYER_SELECT), _settings(Settings()), _hasSave(false), _mapSize(std::make_pair(0, 0)) {
	//std::cout << "Constructing Game\n";
	for (int i = 0; i < 7; i++) {
		this->_keyPressArr[i] = false;
	}
	if (this->checkPlayers().size() > 0)
		this->_hasSave = true;
	this->_player.setSpeed(0.1f);
	std::cout << "Game Constructed\n";
}

Game::Game(Game const & src) {
	*this = src;
	//std::cout << "Game Copy-Constructed\n";
}

Game::~Game() {
	//std::cout << "De-Constructing Game\n";
	if (this->_player.getName().size() > 0)
		savePlayer();
	//std::cout << "Game De-Constructed\n";
}

Game &					Game::operator=(Game const & src) {
	this->_gameState = src.getGameState();
	this->_playState = src.getPlayState();
	for (int i = 0; i < 7; i++) {
		this->_keyPressArr[i] = src.getKeyPressArr(i);
	}
	this->_settings = src.getSettings();
	this->_settings = src.getSettings();
	this->_enemies = src.getEnemies();
	return (*this);
}

GameState				Game::getGameState() const {
	return (this->_gameState);
}

void					Game::setGameState(const GameState newState) {
	this->_gameState = newState;
}

PlayState				Game::getPlayState() const {
	return (this->_playState);
}

void					Game::setPlayState(const PlayState newState) {
	this->_playState = newState;
}

bool					Game::getKeyPressArr(const int index) const {
	return (this->_keyPressArr[index]);
}

void					Game::setKeyPressArr(const int index, const bool newState){
	this->_keyPressArr[index] = newState;
}

Settings				Game::getSettings() const {
	return (this->_settings);
}

void					Game::setSettings(const Settings newSettings) {
	this->_settings = newSettings;
	updateSound();
}

Player					Game::getPlayer() const {
	return (this->_player);
}

void					Game::setPlayer(const Player newPlayer) {
	this->_player = newPlayer;
	this->_settings.setLastPlayer(newPlayer.getName());
}

Sound				&	Game::getSound() {
	return (this->_sound);
}

void					Game::setSound(Sound newSound) {
	this->_sound = newSound;
}

std::vector<Enemy>	Game::getEnemies() const {
	return (this->_enemies);
}

void					Game::setEnemies(const std::vector<Enemy> newEnemies) {
	this->_enemies = newEnemies;
}

std::vector<BreakableBox>	Game::getBreakableBs() const {
	return (this->_breakableBs);
}

void						Game::setBreakableBs(const std::vector<BreakableBox> newBreakableBs) {
	this->_breakableBs = newBreakableBs;
}

std::vector<UnbreakableBox>	Game::getUnbreakableBs() const {
	return (this->_unbreakableBs);
}

void						Game::setUnbreakableBs(const std::vector<UnbreakableBox> newUnbreakableBs) {
	this->_unbreakableBs = newUnbreakableBs;
}

std::vector<Drop*>			Game::getDrops() const {
	return (this->_drops);
}

void					Game::setDrops(const std::vector<Drop*> newDrops) {
	this->_drops = newDrops;
}

std::pair<int, int>		Game::getMapSize() const {
	return (this->_mapSize);
}

void					Game::setMapSize(const std::pair<int, int> newMapSize) {
	this->_mapSize = newMapSize;
}

int						Game::getRange() const {
	return (this->_range);
}

void					Game::setRange(const int newRange) {
	this->_range = newRange;
}

void					Game::savePlayer() {
	DIR							*dir;

	if ((dir = opendir ("resources/profiles/")) == NULL) {
		mkdir("resources/profiles/", 0775);
	}
	std::cout << "Saving profile to : " << this->_player.getFileLocation() << std::endl;
	std::ofstream profileFileOut(this->_player.getFileLocation(), std::ofstream::out);
	profileFileOut << "level:" + (std::to_string(this->_player.getLevel()))+"\n";
	profileFileOut << "experience:" + (std::to_string(this->_player.getExperience()))+"\n";
	profileFileOut << "noOfBombs:" + (std::to_string(this->_player.getNumberOfBombs()))+"\n";
	profileFileOut << "difficulty:" + (std::to_string(this->_player.getDifficulty()))+"\n";
	profileFileOut << "resolutionX:" + (std::to_string(this->_settings.getResolutionX()))+"\n";
	profileFileOut << "resolutionY:" + (std::to_string(this->_settings.getResolutionY()))+"\n";
	if (this->_settings.getWindowed())
		profileFileOut << "windowed:true\n";
	else
		profileFileOut << "windowed:false\n";
	profileFileOut << "upKey:" + (std::to_string(this->_settings.getUpKey()))+"\n";
	profileFileOut << "downKey:" + (std::to_string(this->_settings.getDownKey()))+"\n";
	profileFileOut << "leftKey:" + (std::to_string(this->_settings.getLeftKey()))+"\n";
	profileFileOut << "rightKey:" + (std::to_string(this->_settings.getRightKey()))+"\n";
	profileFileOut << "actionKey:" + (std::to_string(this->_settings.getActionKey()))+"\n";
	profileFileOut << "acceptKey:" + (std::to_string(this->_settings.getAcceptKey()))+"\n";
	profileFileOut << "escapeKey:" + (std::to_string(this->_settings.getEscapeKey()))+"\n";
	profileFileOut << "musicVol:" + (std::to_string(this->_settings.getMusicVol()))+"\n";
	profileFileOut << "FXVol:" + (std::to_string(this->_settings.getFXVol()))+"\n";
	profileFileOut.close();
	std::cout << "Profile for " << this->_player.getName() << " saved to: " << this->_player.getFileLocation() << std::endl;
}

std::vector<std::string>		Game::checkPlayers() const {
	DIR							*dir;
	struct dirent				*ent;
	std::vector<std::string>	arr;
	char						*temp;
	int							len;

	//std::cout << "Checking for old players.\n";
	if ((dir = opendir ("resources/profiles/")) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
				temp = strstr(ent->d_name, ".profile");
				if (temp) {
					len = temp - ent->d_name;
					std::string push(ent->d_name, len);
					//std::cout << "Adding: " << push << std::endl;
					arr.push_back(push);
				}
			}
		}
		closedir(dir);
	}
	return (arr);
}

void					Game::loadPlayer(const std::string playerName) {
	DIR							*dir;
	struct dirent				*ent;
	char						*temp;
	bool						flag = false;
	int							len = 0;

	if ((dir = opendir ("resources/profiles/")) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
				temp = strstr(ent->d_name, ".profile");
				len = temp - ent->d_name;
				if (temp) {
					std::string test(ent->d_name, len);
					if (test == playerName) {
						flag = true;
						std::cout << "Loading player: " + playerName + "\n";
						std::string fileName = "resources/profiles/" + playerName + ".profile";
						this->_player.setFileLocation(fileName);
						this->_player.setName(playerName);
						this->_player.setLevel(std::stoi(lexFile(fileName, "level")));
						this->_player.setExperience(std::stoi(lexFile(fileName, "experience")));
						this->_player.setNumberOfBombs(std::stoi(lexFile(fileName, "noOfBombs")));
						this->_player.setDifficulty(std::stoi(lexFile(fileName, "difficulty")));
						int resX = std::stoi(lexFile(fileName, "resolutionX"));
						int resY = std::stoi(lexFile(fileName, "resolutionY"));
						std::pair<int, int> resolution = std::make_pair(resX, resY);
						this->_settings.setResolution(resolution);

						std::string ret = lexFile(fileName, "windowed");
						if (ret == "false")
							this->_settings.setWindowed(false);
						else
							this->_settings.setWindowed(true);

						this->_settings.setUpKey(std::stoi(lexFile(fileName, "upKey")));
						this->_settings.setDownKey(std::stoi(lexFile(fileName, "downKey")));
						this->_settings.setLeftKey(std::stoi(lexFile(fileName, "leftKey")));
						this->_settings.setRightKey(std::stoi(lexFile(fileName, "rightKey")));
						this->_settings.setActionKey(std::stoi(lexFile(fileName, "actionKey")));
						this->_settings.setAcceptKey(std::stoi(lexFile(fileName, "acceptKey")));
						this->_settings.setEscapeKey(std::stoi(lexFile(fileName, "escapeKey")));
						this->_settings.setMusicVol(std::stoi(lexFile(fileName, "musicVol")));
						this->_settings.setFXVol(std::stoi(lexFile(fileName, "FXVol")));
						std::cout << "Post loading player profile!\n" << this->_settings << std::endl;
						this->updateSound();
					}
				}
			}
		}
		if (flag == false)
			throw (Exceptions::LoadPlayerError(playerName));
		closedir(dir);
	}
}

std::string				Game::lexFile(const std::string fileName, const std::string find) {
	std::ifstream handle(fileName);
	std::string line;
	std::string key;
	std::string value;

	if (!handle)
		throw (Exceptions::LexOpenFileError(fileName));
	else
	{
		while (std::getline(handle, key, ':')) {
			std::getline(handle, value);
			if (key == find) {
				//std::cout << "Found: " << value << " for key " << find << std::endl;
				return value;
			}
			//std::cout << "Looking for key: " << find << "\tFound key: " << key << std::endl;
		}
		throw (Exceptions::LexKeyNotFound(find));
	}	
	return ("ERROR");
}

void					Game::setWindowPos(const int xPos, const int yPos) {
	//std::cout << "Setting Xpos: " << xPos << " yPos: " << yPos << std::endl;
	this->_settings.setXPos(xPos);
	this->_settings.setYPos(yPos);
}

void					Game::initSound() {
	this->_sound.init();
	this->_sound.setVerbose(false);
}

void					Game::updateSound() {
	std::cout << "Update sound called in Game" << std::endl;
	this->_sound.setMusicVol(this->_settings.getMusicVol());
	this->_sound.setFXVol(this->_settings.getFXVol());
	this->_sound.updateMusicVol();
	this->_sound.updateFXVol();
}

void					Game::startMenuMusic() {
	this->_sound.startMenuMusic();
}

void					Game::pauseMenuMusic() {
	this->_sound.pauseMenuMusic();
}

void					Game::resumeMenuMusic() {
	this->_sound.resumeMenuMusic();
}

void					Game::stopMenuMusic() {
	this->_sound.stopMenuMusic();
}

void					Game::startGameMusic() {
	this->_sound.startGameMusic();
}

void					Game::pauseGameMusic() {
	this->_sound.pauseGameMusic();
}

void					Game::resumeGameMusic() {
	this->_sound.resumeGameMusic();
}

void					Game::stopGameMusic() {
	this->_sound.stopGameMusic();
}

void					Game::startCreditsMusic() {
	this->_sound.startCreditsMusic();
}

void					Game::pauseCreditsMusic() {
	this->_sound.pauseCreditsMusic();
}

void					Game::resumeCreditsMusic() {
	this->_sound.resumeCreditsMusic();
}

void					Game::stopCreditsMusic() {
	this->_sound.stopCreditsMusic();
}

void					Game::setPlayerLevel(const int level) {
	_player.setLevel(level);
}

int						Game::getPlayerLevel() {
	return (_player.getLevel());
}

void					Game::setDifficulty(const int dif) {
	this->_player.setDifficulty(dif);
}

void					Game::processEnemies() {
	std::pair<float, float> curPos;
	std::vector<char>		unable;

	for (std::vector<Enemy>::iterator it = _enemies.begin(); it != _enemies.end(); ++it) {
		unable.clear();
		curPos = it->getXY();
		for (int i = 0; i < 4; i++) {
			if (curPos != it->getXY())
				break ;
			it->determineNewCoOrds(_player.getXY(), unable);
			if (it->getNewCoOrd() != it->getXY() && checkCoOrd(it->getNewCoOrd()))
				it->setXY(it->getNewCoOrd());
			else if (it->getNewCoOrd() == it->getXY())
				it->attack();
			else
				unable.push_back(it->getOri());
		}
	}
}

bool					Game::checkCoOrd(std::pair<float, float> xy) {
	bool	ret = true;

	for (std::vector<Enemy>::iterator it = _enemies.begin(); it != _enemies.end(); ++it) {
		if (it->getXY() == xy)
			ret = false;
	}
	for (std::vector<BreakableBox>::iterator it = _breakableBs.begin(); it != _breakableBs.end(); ++it) {
		if (it->getXY() == xy)
			ret = false;
	}
	for (std::vector<UnbreakableBox>::iterator it = _unbreakableBs.begin(); it != _unbreakableBs.end(); ++it) {
		if (it->getXY() == xy)
			ret = false;
	}
	for (std::vector<Drop*>::iterator it = _drops.begin(); it != _drops.end(); ++it) {
		if ((*it)->getXY() == xy)
			ret = false;
	}
	return (ret);
}

bool 					Game::checkCoOrd(std::pair<float, float> xy, char *type) {
	bool	ret = true;

	*type = 'n';
	for (std::vector<Enemy>::iterator it = _enemies.begin(); it != _enemies.end(); ++it) {
		if (it->getXY() == xy) {
			ret = false;
			*type = 'e';
		}
	}
	for (std::vector<BreakableBox>::iterator it = _breakableBs.begin(); it != _breakableBs.end(); ++it) {
		if (it->getXY() == xy) {
			ret = false;
			*type = 'b';
		}
	}
	for (std::vector<UnbreakableBox>::iterator it = _unbreakableBs.begin(); it != _unbreakableBs.end(); ++it) {
		if (it->getXY() == xy) {
			ret = false;
			*type = 'u';
		}
	}
	for (std::vector<Drop*>::iterator it = _drops.begin(); it != _drops.end(); ++it) {
		if ((*it)->getXY() == xy) {
			ret = false;
			*type = 'd';
		}
	}
	return (ret);
}

void				Game::controller() {
	static int 		dropBombDelayTimer = 60;
	if (_keyPressArr[UP])
		moveUp();
	if (_keyPressArr[DOWN])
		moveDown();
	if (_keyPressArr[LEFT])
		moveLeft();
	if (_keyPressArr[RIGHT])
		moveRight();
	if (_keyPressArr[ACTION])
		dropBomb(&dropBombDelayTimer);
	dropBombDelayTimer++;
}

void				Game::moveUp() {
	float 						dist = _player.getSpeed() / 60;
	float 						widthOffset = (_player.getSize() / 2);
	std::pair<float, float> 	tempXY = _player.getXY();
	std::pair<int, int>			castTempXY;
	char 						collisionType = 'n';

	tempXY.first = tempXY.first + 0.5f;
	tempXY.second = tempXY.second + dist + widthOffset + 0.5f;
	castTempXY = std::make_pair((int)tempXY.first, (int)tempXY.second);
	checkCoOrd(castTempXY, &collisionType);
	if (collisionType != 'b' && collisionType != 'u')
		_player.setXY(std::make_pair(_player.getXY().first, _player.getXY().second + dist));
}

void				Game::moveDown() {
	float 						dist = _player.getSpeed() / 60;
	float 						widthOffset = (_player.getSize() / 2);
	std::pair<float, float> 	tempXY = _player.getXY();
	std::pair<int, int>			castTempXY;
	char 						collisionType = 'n';

	tempXY.first = tempXY.first + 0.5f;
	tempXY.second = tempXY.second - dist - widthOffset + 0.5f;
	castTempXY = std::make_pair((int)tempXY.first, (int)tempXY.second);
	checkCoOrd(castTempXY, &collisionType);
	if (collisionType != 'b' && collisionType != 'u')
		_player.setXY(std::make_pair(_player.getXY().first, _player.getXY().second - dist));
}

void				Game::moveLeft() {
	float 						dist = _player.getSpeed() / 60;
	float 						widthOffset = (_player.getSize() / 2);
	std::pair<float, float> 	tempXY = _player.getXY();
	std::pair<int, int>			castTempXY;
	char 						collisionType = 'n';

	tempXY.first = tempXY.first - dist - widthOffset + 0.5f;
	tempXY.second = tempXY.second + 0.5f;
	castTempXY = std::make_pair((int)tempXY.first, (int)tempXY.second);
	checkCoOrd(castTempXY, &collisionType);
	if (collisionType != 'b' && collisionType != 'u')
		_player.setXY(std::make_pair(_player.getXY().first - dist, _player.getXY().second));
}

void				Game::moveRight() {
	float 						dist = _player.getSpeed() / 60;
	float 						widthOffset = (_player.getSize() / 2);
	std::pair<float, float> 	tempXY = _player.getXY();
	std::pair<int, int>			castTempXY;
	char 						collisionType = 'n';

	tempXY.first = tempXY.first + dist + widthOffset + 0.5f;
	tempXY.second = tempXY.second + 0.5f;
	castTempXY = std::make_pair((int)tempXY.first, (int)tempXY.second);
	checkCoOrd(castTempXY, &collisionType);
	if (collisionType != 'b' && collisionType != 'u')
		_player.setXY(std::make_pair(_player.getXY().first + dist, _player.getXY().second));
}

void				Game::dropBomb(int *delayTimer) {
	std::pair<float, float>		bombXY;

	bombXY = std::make_pair((int)(_player.getXY().first + 0.5), (int)(_player.getXY().second + 0.5));
	if (*delayTimer >= 60) {
		*delayTimer = 0;
	}
}

std::ostream & 			operator<<(std::ostream & o, Game const & rhs) {
	int size;
	o << "Dumping Game State" <<
	"\nGame State: " << static_cast<std::underlying_type<GameState>::type>(rhs.getGameState()) <<
	"\nPlay State: " << static_cast<std::underlying_type<PlayState>::type>(rhs.getPlayState()) <<
	"\nMap Size: " << rhs.getMapSize().first << " x " << rhs.getMapSize().second << std::endl;
	for (int i = 0; i < 7; i++) {
		o << "keyPressArr[" << i << "]: " << std::boolalpha << rhs.getKeyPressArr(i) << std::endl;
	}

	if ((size = rhs.getEnemies().size()) > 0) {
		std::vector<Enemy> tempEnemy = rhs.getEnemies();
		for (int i = 0; i < size; i++)
			o << "Enemy " << i << "\tX: " << tempEnemy[i].getXY().first << "\tY: " << tempEnemy[i].getXY().second << std::endl;
	}
	else
		o << "Enemies: 0\n";

	if ((size = rhs.getBreakableBs().size()) > 0) {
		std::vector<BreakableBox> tempBB = rhs.getBreakableBs();
		for (int i = 0; i < size; i++)
			o << "Breakable Box " << i << "\tX: " << tempBB[i].getXY().first << "\tY: " << tempBB[i].getXY().second << std::endl;
	}
	else
		o << "Breakable Box: 0\n";

	if ((size = rhs.getUnbreakableBs().size()) > 0) {
		std::vector<UnbreakableBox> tempUB = rhs.getUnbreakableBs();
		for (int i = 0; i < size; i++)
			o << "Unbreakable Box " << i << "\tX: " << tempUB[i].getXY().first << "\tY: " << tempUB[i].getXY().second << std::endl;
	}
	else
		o << "Unbreakable Box: 0\n";

	if ((size = rhs.getDrops().size()) > 0) {
		std::vector<Drop*> tempDrp = rhs.getDrops();
		for (int i = 0; i < size; i++)
			o << "Drop " << i << "\tX: " << tempDrp[i]->getXY().first << "\tY: " << tempDrp[i]->getXY().second << std::endl;
	}
	else
		o << "Drops: 0\n";
	
	o << "\nSettings: " << rhs.getSettings() << std::endl << "Player: " << rhs.getPlayer();
	return o;
}

void					Game::unbreakableRing(int x, int y) {
	int		xStart = (_mapSize.first - x);
	int		yStart = (_mapSize.second - y);
	std::cout << "Passed x: " << x << " Passed y: " << y << " xStart: " << xStart << " yStart: " << yStart << std::endl;

	for (int i = xStart; i < x; i++) {
		if (i == xStart || i == x-1) {
			for (int j = yStart; j < y; j++) {
				_unbreakableBs.push_back(UnbreakableBox(std::make_pair(i, j)));
			}
		}
		if (i > xStart && i < x-1) {
			_unbreakableBs.push_back(UnbreakableBox(std::make_pair(i, yStart)));
			_unbreakableBs.push_back(UnbreakableBox(std::make_pair(i, y-1)));
		}
	}
}

void					Game::breakableRing(int x, int y) {
	int		xStart = (_mapSize.first - x);
	int		yStart = (_mapSize.second - y);
	std::cout << "Passed x: " << x << " Passed y: " << y << " xStart: " << xStart << " yStart: " << yStart << std::endl;

	for (int i = xStart; i < x; i++) {
		if (i == xStart || i == x-1) {
			for (int j = yStart; j < y; j++) {
				_breakableBs.push_back(BreakableBox(std::make_pair(i, j)));
			}
		}
		if (i > xStart && i < x-1) {
			_breakableBs.push_back(BreakableBox(std::make_pair(i, yStart)));
			_breakableBs.push_back(BreakableBox(std::make_pair(i, y-1)));
		}
	}
}

void					Game::breakableRing(int x, int y, std::pair<int, int> skip) {
	int		xStart = (_mapSize.first - x);
	int		yStart = (_mapSize.second - y);
	std::pair<int, int>	temp;
	std::cout << "Passed x: " << x << " Passed y: " << y << " xStart: " << xStart << " yStart: " << yStart << std::endl;

	for (int i = xStart; i < x; i++) {
		if (i == xStart || i == x-1) {
			for (int j = yStart; j < y; j++) {
				temp = std::make_pair(i, j);
				if (temp != skip)
					_breakableBs.push_back(BreakableBox(temp));
			}
		}
		if (i > xStart && i < x-1) {
			temp = std::make_pair(i, yStart);
			if (temp != skip)
				_breakableBs.push_back(BreakableBox(temp));
			temp = std::make_pair(i, y-1);
			if (temp != skip)
				_breakableBs.push_back(BreakableBox(temp));
		}
	}
}

void					Game::cornerBox(int x, int y) {
	int		x1 = (_mapSize.first - x);
	int		x2 = x - 1;
	int		y1 = (_mapSize.second - y);
	int		y2 = y - 1;

	std::cout << "Doing corners\n";
	_breakableBs.push_back(BreakableBox(std::make_pair(x1, y1)));
	_breakableBs.push_back(BreakableBox(std::make_pair(x1, y2)));
	_breakableBs.push_back(BreakableBox(std::make_pair(x2, y1)));
	_breakableBs.push_back(BreakableBox(std::make_pair(x2, y2)));
}

int					Game::dropFreeBoxInd() {
	int		randomInt;

	while (1) {
		randomInt = rand() % _breakableBs.size();
		std::cout << "Random Int = " << randomInt << " size = " << _breakableBs.size() << std::endl;
		if (!_breakableBs[randomInt].getDrop())
			return (randomInt);
	}
}

void					Game::initLevelOne() {
	int		index;
	//determine _mapSize
	_mapSize = std::make_pair(_player.getDifficulty() * 10, _player.getDifficulty() * 10);
	//Spawn Boxes
	unbreakableRing(_mapSize.first, _mapSize.second);
	for (int i = 1; i < (_mapSize.first / 2); i++) {
		if (i % 2 == 0) {
			if (i == 2)
				breakableRing(_mapSize.first - i, _mapSize.second - i, std::make_pair(2, 2));
			else
				breakableRing(_mapSize.first - i, _mapSize.second - i);
		}
		else
			cornerBox(_mapSize.first - i, _mapSize.second - i);
	}
	//Spawn Player
	_player.setXY(std::make_pair(2, 2));
	//Randomize one of each Drop
	index = dropFreeBoxInd();
	_breakableBs[index].setDrop(new LevelHatch(_breakableBs[index].getXY()));
	index = dropFreeBoxInd();
	_breakableBs[index].setDrop(new RemoteDetonator(_breakableBs[index].getXY()));
	if (_player.getLevel() == 0) {
		index = dropFreeBoxInd();
		_breakableBs[index].setDrop(new ExtraBomb(_breakableBs[index].getXY()));
		index = dropFreeBoxInd();
		_breakableBs[index].setDrop(new RangeExtender(_breakableBs[index].getXY()));
	}
}

void					Game::initLevelTwo() {
	//int		index;
	//determine _mapSize
	_mapSize = std::make_pair(_player.getDifficulty() * 10, _player.getDifficulty() * 10);
	//Spawn Boxes
	unbreakableRing(_mapSize.first, _mapSize.second);
	for (int i = 1; i < (_mapSize.first / 2); i++) {
		//cornerBox(_mapSize.first - i, _mapSize.second - i);
	}
}

void					Game::initLevelThree() {
}

void					Game::reset() {
	_enemies.clear();
	_breakableBs.clear();
	_unbreakableBs.clear();
	_drops.clear();
}