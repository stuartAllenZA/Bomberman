#include <Game.hpp>

Game::Game() : _gameState(GameState::MENU), _playState(PlayState::PLAYER_SELECT), _gameInput(0), _settings(Settings()), _hasSave(false) {
	std::cout << "Constructing Game\n";
	loadSettings();
	std::cout << "Game Constructed\n";
}

Game::Game(Game const & src) {
	*this = src;
	std::cout << "Game Copy-Constructed\n";
}

Game::~Game() {
	std::cout << "De-Constructing Game\n";
	saveSettings();
	std::cout << "Game De-Constructed\n";
}

Game &					Game::operator=(Game const & src) {
	this->_gameState = src.getGameState();
	this->_playState = src.getPlayState();
	this->_gameInput = src.getGameInput();
	this->_settings = src.getSettings();
	this->_player = src.getPlayer();
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

int						Game::getGameInput() const {
	return (this->_gameInput);
}

void					Game::setGameInput(const int newInput) {
	this->_gameInput = newInput;
}

Settings				Game::getSettings() const {
	return (this->_settings);
}

void					Game::setSettings(const Settings newSettings) {
	this->_settings = newSettings;
}

Player					Game::getPlayer() const {
	return (this->_player);
}

void					Game::setPlayer(const Player newPlayer) {
	this->_player = newPlayer;
}

std::vector<Character*>	Game::getEnemies() const {
	return (this->_enemies);
}

void					Game::setEnemies(const std::vector<Character*> newEnemies) {
	this->_enemies = newEnemies;
}

bool 					Game::getHasSave() const{
	return (this->_hasSave);
}

void 					Game::setHasSave(const bool newHasSave){
	this->_hasSave = newHasSave;
}

void					Game::saveSettings() {
	std::ofstream settingsOut("resources/bomberman.config", std::ofstream::out);
	settingsOut << "resolutionX:" + (std::to_string(this->_settings.getResolutionX()))+"\n";
	settingsOut << "resolutionY:" + (std::to_string(this->_settings.getResolutionY()))+"\n";
	if (this->_settings.getWindowed())
		settingsOut << "windowed:true\n";
	else
		settingsOut << "windowed:false\n";
	settingsOut << "upKey:" + (std::to_string(this->_settings.getUpKey()))+"\n";
	settingsOut << "downKey:" + (std::to_string(this->_settings.getDownKey()))+"\n";
	settingsOut << "leftKey:" + (std::to_string(this->_settings.getLeftKey()))+"\n";
	settingsOut << "rightKey:" + (std::to_string(this->_settings.getRightKey()))+"\n";
	settingsOut << "actionKey:" + (std::to_string(this->_settings.getActionKey()))+"\n";
	settingsOut << "musicVol:" + (std::to_string(this->_settings.getMusicVol()))+"\n";
	settingsOut << "FXVol:" + (std::to_string(this->_settings.getFXVol()))+"\n";
	settingsOut.close();
	std::cout << "Settings saved to ./resources/bomberman.config.\n";
}

void					Game::savePlayer() {
	std::ofstream profileFileOut("resources/profiles/" + this->_player.getName() + ".player", std::ofstream::out);
	profileFileOut << "level:" + (std::to_string(this->_player.getLevel()))+"\n";
	profileFileOut << "experience:" + (std::to_string(this->_player.getExperience()))+"\n";
	profileFileOut.close();
	std::cout << "Player saved to ./resources/profiles/" << this->_player.getName() << ".player\n";
}

void					Game::saveGame() {
	std::ofstream saveFileOut("resources/save/" + this->_player.getName() + ".save", std::ofstream::out);
	// insert save data here
	// e.g.	saveFileOut << "playerHP:"+(std::to_string(_player.getHP()))+"\n";
	saveFileOut.close();
	std::cout << "Game saved to ./resources/profiles/" << this->_player.getName() << ".save\n";
}

void					Game::loadPlayer(std::string playerName) {
	std::string fileName = "resources/profiles/" + playerName + ".profile";
	this->_player.setLevel(std::stoi(lexFile(fileName, "level")));
	this->_player.setExperience(std::stoi(lexFile(fileName, "experience")));
}

void					Game::loadGame() {
}

void					Game::loadSettings() {
	std::string fileName = "resources/bomberman.config";
	struct stat buffer;

	std::cout << "Loading Settings\n";
	if (stat(fileName.c_str(), &buffer) != 0)
		std::cout << "Cannot find file '" << fileName << "'. Using default settings.\n";
	else {
		std::cout << "Config file found at: '" << fileName << "'. Using saved settings.\n";
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
		this->_settings.setMusicVol(std::stoi(lexFile(fileName, "musicVol")));
		this->_settings.setFXVol(std::stoi(lexFile(fileName, "FXVol")));
	}
}

std::string				Game::lexFile(std::string fileName, std::string find) {
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

void					Game::startBackgroundMusic() {
	this->_sound.startMenuMusic();
}

void					Game::stopBackgroundMusic() {
	this->_sound.stopMenuMusic();
}

std::ostream & 			operator<<(std::ostream & o, Game const & rhs) {
	int num = 0;
	o << "Dumping Game State" <<
	"\nGame State: " << static_cast<std::underlying_type<GameState>::type>(rhs.getGameState()) <<
	"\nPlay State: " << static_cast<std::underlying_type<PlayState>::type>(rhs.getPlayState()) <<
	"\nGame Input: " << rhs.getGameInput() << std::endl <<
	"\nPlayer: " << rhs.getPlayer();
	if (rhs.getEnemies().size() > 0) {
		for (std::vector<Character*>::iterator it = rhs.getEnemies().begin(); it != rhs.getEnemies().end(); ++it)
		{
			num++;
			o << "Enemy " << num << ": " << *it << std::endl;
		}
	}
	else
		o << "Enemies: 0\n";
	o << rhs.getSettings() << std::endl;
	return o;
}

/*
void				Game::up() {
	// update coords x++;
}

void				Game::updateGameData() {
	switch (_gameInput) {
		case UP:
		case DOWN:
		case LEFT:
		case RIGHT:
		case SPACE:
		case ESC:
	}
	// detectCollisions
	// AIBehaveUpdate
	// detectCollisions
}

// map has to have an odd number of x's and y's
// i.e. maxX and maxY must be even numbers (starting at 0)
void				Game::mapGenerator(int xMax, int yMax) {
	for (int xmin = 0; xmin < xmax; xmin++) {
		for (int ymin = 0; ymin < ymax; ymin++) {
			if (xmin != 0 && ymin != 0 && xmin != xmax && ymin != ymax) {
				if (xmin % 2 == 0 && ymin % 2 == 0) {
					unbreakableWallTemp	unbreakableWall(xmin, ymin);
					_unbreakableWalls.push_back(*unbreakableWall);
				}
			}
			else if (xmin == 0 || xmin == xmax || ymin == 0 || ymin == ymax) {
				unbreakableWallTemp	unbreakableWall(xmin, ymin);
				_unbreakableWalls.push_back(*unbreakableWall);
			}
		}
	}
}
*/
