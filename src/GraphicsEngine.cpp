#include <GraphicsEngine.hpp>
#include <Model.hpp>

float previous = 0.0f;
int displayTime = 0;
int displayMin = 0;
//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//camera
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0f;

//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

GraphicsEngine::GraphicsEngine() {}

GraphicsEngine::~GraphicsEngine() {
	delete this->_playerShader;
	delete this->_wallShader;
	delete this->_floorShader;
	delete this->_boxShader;
	delete this->_bombShader;
	delete this->_flameShader;
	delete this->_enemyShader;
	delete this->_dropShader;

	delete this->_playerModel;
	delete this->_wallModel;
	delete this->_floorModel;
	delete this->_boxModel;
	delete this->_bombModel;
	delete this->_flameModel;
	delete this->_enemyModel;
	delete this->_dropModel;

	this->_playerShader = nullptr;
	this->_wallShader = nullptr;
	this->_floorShader = nullptr;
	this->_boxShader = nullptr;
	this->_bombShader = nullptr;
	this->_flameShader = nullptr;
	this->_enemyShader = nullptr;
	this->_dropShader = nullptr;

	this->_playerModel = nullptr;
	this->_wallModel = nullptr;
	this->_floorModel = nullptr;
	this->_boxModel = nullptr;
	this->_bombModel = nullptr;
	this->_flameModel = nullptr;
	this->_enemyModel = nullptr;
	this->_dropModel = nullptr;

}

GraphicsEngine::GraphicsEngine(Game	*game, GLFWwindow **window) : _game(game), _window(*window) { }

GraphicsEngine::GraphicsEngine(GraphicsEngine const & src) {
	*this = src;
}

GraphicsEngine	&GraphicsEngine::operator=(GraphicsEngine const & src) {
	this->_camera = src.getCamera();
	this->_playerShader = src.getPlayerShader();
	this->_wallShader = src.getWallShader();
	this->_floorShader = src.getFloorShader();
	this->_boxShader = src.getBoxShader();
	this->_bombShader = src.getBombShader();
	this->_flameShader = src.getFlameShader();
	this->_enemyShader = src.getEnemyShader();
	this->_dropShader = src.getDropShader();

	this->_playerModel = src.getPlayerModel();
	this->_wallModel = src.getWallModel();
	this->_floorModel = src.getFloorModel();
	this->_boxModel = src.getBoxModel();
	this->_bombModel = src.getBombModel();
	this->_flameModel = src.getFlameModel();
	this->_enemyModel = src.getEnemyModel();
	this->_dropModel = src.getDropModel();
	return (*this);
}

void GraphicsEngine::initSystems() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bomberman", NULL, NULL);
	if (_window == NULL)
	{
		////std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(_window);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);
}

void	GraphicsEngine::initCamera() {
	// init camera
	if (_cameraLoaded)
		_camera.reset();
	_cameraLoaded = true;
	_prevZ = 0.0f;
	_prevX = 0.0f;
	displayTime = 0;
	displayMin = 0;
}

void GraphicsEngine::init() {
	initCamera();
	// init shaders
	_playerShader = new Shader("resources/shaders/anime.vert", "resources/shaders/basic.frag");
	_wallShader = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
	_floorShader = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
	_boxShader = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
	_bombShader = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
	_flameShader = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
	_dropShader = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
//	_doorShader = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
	_enemyShader = new Shader("resources/shaders/anime.vert", "resources/shaders/basic.frag");

	// init models
	_playerShader->enable();
	_playerModel = new Model("resources/models/BMwalk3.gltf", _playerShader);
	_wallModel = new Model("resources/models/Cube.gltf", _wallShader);
//	_wallModel = new Model("resources/models/scene.gltf", _wallShader);
	_floorModel = new Model("resources/models/BMfloor.gltf", _floorShader);
	_boxModel = new Model("resources/models/block1.gltf", _boxShader);
	_bombModel = new Model("resources/models/BMbomb.gltf", _bombShader);
	_flameModel = new Model("resources/models/BMflame.gltf", _flameShader);
	//_enemyModel = new Model("resources/models/MechGoblin_Anim_Walk01.gltf", _enemyShader);
	_enemyModel = new Model("resources/models/man.gltf", _enemyShader);
	_dropModel = new Model("resources/models/BMflame.gltf", _dropShader);
	//_dropModel = new Model("resources/models/BMextraflame.gltf", _dropShader);
//	_dropModel = new Model("resources/models/BMextrabombNEW.gltf", _dropShader);
	_doorModel = new Model("resources/models/BMtrapdoor.gltf", _dropShader);
	_flameExtModel = new Model("resources/models/BMextraflame.gltf", _dropShader);
	_extBombModel = new Model("resources/models/BMextrabombNEW.gltf", _dropShader);

	std::pair<float, float> coords;
	coords = _game->getPlayer().getXY();
	glm::mat4 view = _camera.getViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
	_playerRotate = -0.01f;	
	glm::vec3 rotationAxis(0.0f, 1.0f, 0.0f);
	glm::mat4 scalar = glm::scale(glm::mat4(), glm::vec3(1.2f, 1.2f, 1.2f));
	glm::mat4 rotator = glm::rotate(glm::mat4(), _playerRotate, rotationAxis);
	glm::mat4 translator = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2))); 
	glm::mat4 transform = translator * rotator * scalar;
	_playerMatrice = transform;
	_playerModel->renderAnimated(_playerMatrice, view, projection);
	 //_playerMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_wallMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_boxMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_bombMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_flameMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_floorMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
//	_enemyMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	
	int vecSize;	
	_enemyShader->enable();
	std::vector<Enemy> tempEnmy = _game->getEnemies();
	vecSize = tempEnmy.size();
	for (int i = 0; i < vecSize; i++) {
		coords = tempEnmy[i].getXY();
		if (tempEnmy[i].getOri() == 'N')
			_enemyRotate = 135.1f;	
		else if (tempEnmy[i].getOri() == 'S')
			_enemyRotate = -0.01f;	
		else if (tempEnmy[i].getOri() == 'E')
			_enemyRotate = -80.0f;	
		else if (tempEnmy[i].getOri() == 'W')
			_enemyRotate = 80.0f;	
	//	glm::vec4 enemyPosition(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 enemyRotationAxis(0.0f, 1.0f, 0.0f);
		glm::mat4 enemyScalar = glm::scale(glm::mat4(), glm::vec3(0.4f, 0.4f, 0.4f));
		glm::mat4 enemyRotator = glm::rotate(glm::mat4(), _playerRotate, rotationAxis);
		glm::mat4 enemyTranslator = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2.0f))); 
		glm::mat4 enemyTransform = enemyTranslator * enemyRotator * enemyScalar;
		_enemyMatrice = enemyTransform;
		_enemyModel->renderAnimated(_enemyMatrice, view, projection);
	}

	_dropMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
}

void GraphicsEngine::render() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	std::pair<float, float> coords;
	int vecSize;	

	coords = _game->getPlayer().getXY();
	if (_prevZ != coords.second) {
		if (_game->getKeyPressArr(UP))
			_camera.changeCameraZPos(-_game->getPlayer().getSpeed() / 30.0f);
		else if (_game->getKeyPressArr(DOWN))
			_camera.changeCameraZPos(_game->getPlayer().getSpeed() / 30.0f);
	}
	if (_prevX != coords.first) {
		if (_game->getKeyPressArr(RIGHT))
			_camera.changeCameraXPos(_game->getPlayer().getSpeed() / 30.0f);
		else if (_game->getKeyPressArr(LEFT))
			_camera.changeCameraXPos(-_game->getPlayer().getSpeed() / 30.0f);
	}
	glm::mat4 view = _camera.getViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

	_isAnime = false;
	if (_game->getKeyPressArr(UP)) {
		_playerRotate = 135.1f;	
		_isAnime = true;
	}
	else if (_game->getKeyPressArr(LEFT)) {
		_playerRotate = 80.0f;	
		_isAnime = true;
	}
	else if (_game->getKeyPressArr(RIGHT)) {
		_playerRotate = -80.0f;	
		_isAnime = true;
	}
	else if (_game->getKeyPressArr(DOWN)) {
		_playerRotate = -0.01f;	
		_isAnime = true;
	}
	///
//	glm::vec4 myPosition(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 rotationAxis(0.0f, 1.0f, 0.0f);
	glm::mat4 scalar = glm::scale(glm::mat4(), glm::vec3(1.2f, 1.2f, 1.2f));
	glm::mat4 rotator = glm::rotate(glm::mat4(), _playerRotate, rotationAxis);
	glm::mat4 translator = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2))); 
	///

	glm::mat4 transform = translator * rotator * scalar;
	_playerShader->enable();
	_playerMatrice = transform;

	if (_isAnime)
		_playerModel->renderAnimated(_playerMatrice, view, projection);
	else _playerModel->render(_playerMatrice, view, projection);

	_prevZ = coords.second;
	_prevX = coords.first;

	// BOMBS
	_bombShader->enable();
	std::vector<Bomb> bombs= _game->getBombs();
	vecSize = bombs.size();
	for (int i = 0; i < vecSize; i++) {
		coords = bombs[i].getXY();
		//std::cout << "coords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_bombMatrice = glm::translate(glm::mat4(), glm::vec3(coords.first * 2.0f, 0.0f, (-1 * coords.second * 2.0f))); 
		_bombModel->render(_bombMatrice, view, projection);
	}

	std::vector<Flame> flames= _game->getFlames();
	vecSize = flames.size();
	for (int i = 0; i < vecSize; i++) {
		coords = flames[i].getXY();
		//std::cout << "coords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_flameMatrice = glm::translate(glm::mat4(), glm::vec3(coords.first * 2.0f, 0.0f, (-1 * coords.second * 2.0f)));
		_flameModel->render(_flameMatrice, view, projection);
	}

	/// WALLS & BOXES
	_floorShader->enable();
	std::pair<int, int> mapSize = _game->getMapSize();
	float mapX = (float)mapSize.first;
	float mapZ = (float)mapSize.second;

	for (float x = 0.0f; x < mapX; x++) {
		for (float z = 0.0f; z < mapZ; z++) {
			_floorMatrice = glm::translate(glm::mat4(), glm::vec3((x * 2.0), -0.5f, (-1 * z) * 2)); 
			_floorModel->render(_floorMatrice, view, projection);

		}
	}

	_wallShader->enable();
	std::vector<UnbreakableBox> tempUB = _game->getUnbreakableBs();
	vecSize = tempUB.size();
	for (int i = 0; i < vecSize; i++) {
		coords = tempUB[i].getXY();
		_wallMatrice = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2))); 
		_wallModel->render(_wallMatrice, view, projection);
	}

	_boxShader->enable();
	std::vector<BreakableBox> tempBB = _game->getBreakableBs();
	vecSize = tempBB.size();
	for (int i = 0; i < vecSize; i++) {
		coords = tempBB[i].getXY();
		_boxMatrice = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2))); 
		_boxModel->render(_boxMatrice, view, projection);
	}

	/// DROPS & ENEMIES
	_dropShader->enable();
	std::vector<Drop*> tempDrp = _game->getDrops();
	vecSize = tempDrp.size();
	//std::cout << "Doing " << vecSize << " Drops." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempDrp[i]->getXY();
		//std::cout << "coords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_dropMatrice = glm::translate(glm::mat4(), glm::vec3(coords.first * 2.0f, 0.0f, (-1 * coords.second * 2.0f))); 
		if (tempDrp[i]->getDropType() == DropType::LEVEL_HATCH)
		   _doorModel->render(_dropMatrice, view, projection);
		else if (tempDrp[i]->getDropType() == DropType::FLAME_EXT)
		   _flameExtModel->render(_dropMatrice, view, projection);
		else if (tempDrp[i]->getDropType() == DropType::BOMB_ADD)
		   _extBombModel->render(_dropMatrice, view, projection);
	}

	_enemyShader->enable();
	std::vector<Enemy> tempEnmy = _game->getEnemies();
	vecSize = tempEnmy.size();
	for (int i = 0; i < vecSize; i++) {
		coords = tempEnmy[i].getXY();
		if (tempEnmy[i].getOri() == 'N')
			_enemyRotate = 80.0f;	
		else if (tempEnmy[i].getOri() == 'S')
			_enemyRotate = -80.0f;	
		else if (tempEnmy[i].getOri() == 'E')
			_enemyRotate = -0.01f;	
		else if (tempEnmy[i].getOri() == 'W')
			_enemyRotate = 135.1f;	
	//	glm::vec4 enemyPosition(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 enemyRotationAxis(0.0f, 1.0f, 0.0f);
		glm::mat4 enemyScalar = glm::scale(glm::mat4(), glm::vec3(0.4f, 0.4f, 0.4f));
		glm::mat4 enemyRotator = glm::rotate(glm::mat4(), _enemyRotate, rotationAxis);
		glm::mat4 enemyTranslator = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2.0f))); 
		glm::mat4 enemyTransform = enemyTranslator * enemyRotator * enemyScalar;
		_enemyMatrice = enemyTransform;
		_enemyModel->renderAnimated(_enemyMatrice, view, projection);
	}

	displayHUD();

	glfwSwapBuffers(_window);
}

void		GraphicsEngine::displayHUD() {
	//	glUseProgram(getText2DShaderID());
	float current = glfwGetTime();
	if (current - previous >= 1.0f) {
		displayTime++;
		previous = current;
	}
	if (displayTime == 60) {
		displayTime = 0;
		displayMin++;
	}
	glGenVertexArrays(1, &_textVertexArrayID);
	glBindVertexArray(_textVertexArrayID);

	initText2D( "resources/fonts/Holstein.DDS" );

	std::string	healthText = "Health:";
	std::string	health = std::to_string(_game->getPlayer().getHealth());
	std::string bombsText = "Bombs:";
	std::string bombs = std::to_string(_game->getPlayer().getNumberOfBombs());

	printText2D("Time:", 10, 570, 20);
	printText2D((to_string(displayMin)).c_str(), 120, 570, 20);
	printText2D(":", 125, 570, 20);
	printText2D((to_string(displayTime)).c_str(), 130, 570, 20);
	printText2D((healthText+health).c_str(), 10, 545, 20);
	printText2D((bombsText+bombs).c_str(), 10, 520, 20);
}

// getters

Game								*GraphicsEngine::getGame() const {
	return this->_game;
}

GLFWwindow							*GraphicsEngine::getWindow() const {
	return this->_window;
}

Camera								GraphicsEngine::getCamera() const {
	return this->_camera;
}

// setters

void	GraphicsEngine::setGame(Game *game) {
	this->_game = game;
}

void	GraphicsEngine::setWindow(GLFWwindow *window) {
	this->_window = window;
}

void	GraphicsEngine::setCamera(Camera camera) {
	this->_camera = camera;
}

Shader								*GraphicsEngine::getPlayerShader() const {
	return this->_playerShader;
}
Shader								*GraphicsEngine::getWallShader() const {
	return this->_wallShader;
}
Shader								*GraphicsEngine::getFloorShader() const {
	return this->_floorShader;
}
Shader								*GraphicsEngine::getBoxShader() const {
	return this->_boxShader;
}
Shader								*GraphicsEngine::getBombShader() const {
	return this->_bombShader;
}
Shader								*GraphicsEngine::getFlameShader() const {
	return this->_flameShader;
}
Shader								*GraphicsEngine::getEnemyShader() const {
	return this->_enemyShader;
}
Shader								*GraphicsEngine::getDropShader() const {
	return this->_dropShader;
}

Model								*GraphicsEngine::getPlayerModel() const {
	return this->_playerModel;
}
Model								*GraphicsEngine::getWallModel() const {
	return this->_wallModel;
}
Model								*GraphicsEngine::getFloorModel() const {
	return this->_floorModel;
}
Model								*GraphicsEngine::getBoxModel() const {
	return this->_boxModel;
}
Model								*GraphicsEngine::getBombModel() const {
	return this->_bombModel;
}
Model								*GraphicsEngine::getFlameModel() const {
	return this->_flameModel;
}
Model								*GraphicsEngine::getEnemyModel() const {
	return this->_enemyModel;
}
Model								*GraphicsEngine::getDropModel() const {
	return this->_dropModel;
}

