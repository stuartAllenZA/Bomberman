#include <GraphicsEngine.hpp>
#include <Model.hpp>

char axis = 'z';
char direction = 'n';
float z = 0.0f;
float x = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//camera
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::mat4 model;
glm::mat4 model2;

GraphicsEngine::GraphicsEngine() {}

GraphicsEngine::~GraphicsEngine() {
	delete this->_camera;
	_camera = nullptr;
}

GraphicsEngine::GraphicsEngine(Game	*game, GLFWwindow **window) : _game(game), _window(*window) { }

GraphicsEngine::GraphicsEngine(GraphicsEngine const & src) {
	*this = src;
}

GraphicsEngine	&GraphicsEngine::operator=(GraphicsEngine const & src) {
	this->_models = src.getModels();
	this->_matrices = src.getMatrices();
	this->_shaders = src.getShaders();
	this->_game = src.getGame();
	this->_window = src.getWindow();
	this->_camera = src.getCamera();
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

	_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
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

void	GraphicsEngine::resetCamera() {
	if (_camera) {
		delete _camera;
	}
}

void	GraphicsEngine::initCamera() {
	// init camera
	if (_cameraLoaded)
		_camera->reset(glm::vec3(4.0f, 12.0f, 4.0f), -60.0f, -90.0f);
	else _camera = new Camera(glm::vec3(4.0f, 12.0f, 4.0f), -60.0f, -90.0f);
	_cameraLoaded = true;
	_prevZ = 0.0f;
	_prevX = 0.0f;
}

void GraphicsEngine::init() {
	initCamera();

	// init shaders
	_shaders["player"] = new Shader("resources/shaders/anime.vert", "resources/shaders/basic.frag");
	_shaders["wall"] = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
	_shaders["floor"] = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
	_shaders["box"] = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
	_shaders["bomb"] = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
	_shaders["flame"] = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
	_shaders["enemy"] = new Shader("shaders/basic.vert", "gfxUtils/shaders/basic.frag");
	_shaders["drop"] = new Shader("shaders/anime.vert", "gfxUtils/shaders/basic.frag");

	// init models
	_models["player"] = new Model("resources/models/BMwalk3.gltf", _shaders.find("player")->second);
	_models["wall"] = new Model("resources/models/Cube.gltf", _shaders.find("wall")->second);
	_models["floor"] = new Model("resources/models/BMfloor.gltf", _shaders.find("floor")->second);
	_models["box"] = new Model("resources/models/block1.gltf", _shaders.find("box")->second);
	_models["bomb"] = new Model("resources/models/BMbomb.gltf", _shaders.find("bomb")->second);
	_models["flame"] = new Model("resources/models/BMextraflame.gltf", _shaders.find("bomb")->second);
	_models["enemy"] = new Model("resources/models/boneBox.gltf", _shaders.find("enemy")->second);
	_models["drop"] = new Model("resources/models/boneBox.gltf", _shaders.find("drop")->second);
	
	// load init positions
	std::pair<float, float> coords;
	coords = _game->getPlayer().getXY();
	_matrices["player"] = glm::translate(glm::mat4(), glm::vec3(coords.first * 2.0f, 0.0f, coords.second * 2.0f)); 
	_matrices["wall"] = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_matrices["floor"] = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_matrices["box"] = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_matrices["enemy"] = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_matrices["bomb"] = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_matrices["flame"] = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_matrices["drop"] = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	
}

void GraphicsEngine::render() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	std::pair<float, float> coords;
	int vecSize;	
	// 1. rotations
	// 2. background
	// 3. HUD
	/// CAMERA, EVENTS & PLAYER
	coords = _game->getPlayer().getXY();
	if (_prevZ != coords.second) {
		if (_game->getKeyPressArr(UP))
			_camera->changeCameraZPos(-_game->getPlayer().getSpeed() / 30.0f);
		else if (_game->getKeyPressArr(DOWN))
			_camera->changeCameraZPos(_game->getPlayer().getSpeed() / 30.0f);
	}
	if (_prevX != coords.first) {
		if (_game->getKeyPressArr(RIGHT))
			_camera->changeCameraXPos(_game->getPlayer().getSpeed() / 30.0f);
		else if (_game->getKeyPressArr(LEFT))
			_camera->changeCameraXPos(-_game->getPlayer().getSpeed() / 30.0f);
	}
	glm::mat4 view = _camera->getViewMatrix();
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
	////
	glm::vec4 myPosition(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 rotationAxis(0.0f, 1.0f, 0.0f);
	glm::mat4 scalar = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 rotator = glm::rotate(glm::mat4(), _playerRotate, rotationAxis);
	glm::mat4 translator = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2))); 
	///

	glm::mat4 transform = translator * rotator * scalar;
	_shaders.find("player")->second->enable();
	_matrices.find("player")->second = transform;
	
	if (_isAnime)
		_models.find("player")->second->renderAnimated(_matrices.find("player")->second, view, projection);
	else _models.find("player")->second->render(_matrices.find("player")->second, view, projection);

	_prevZ = coords.second;
	_prevX = coords.first;
	if (_game->getKeyPressArr(ACTION)) {
		_shaders.find("bomb")->second->enable();
		_matrices.find("bomb")->second = glm::translate(glm::mat4(), glm::vec3((3.0 * 2.0), 0.0f, ((-1 * 4.0f) * 2))); 
		_models.find("bomb")->second->render(_matrices.find("bomb")->second, view, projection);

		_shaders.find("flame")->second->enable();
		_matrices.find("flame")->second = glm::translate(glm::mat4(), glm::vec3((3.0 * 2.0), 0.0f, ((-1 * 5.0f) * 2))); 
		_models.find("flame")->second->render(_matrices.find("flame")->second, view, projection);

		_shaders.find("enemy")->second->enable();
		_matrices.find("enemy")->second = glm::translate(glm::mat4(), glm::vec3((2.5f * 2.0), 0.0f, ((-1 * 4.0f) * 2))); 
		_models.find("enemy")->second->render(_matrices.find("enemy")->second, view, projection);
	}

	/// WALLS & BOXES
	_shaders.find("floor")->second->enable();
	std::pair<int, int> mapSize = _game->getMapSize();
	float mapX = (float)mapSize.first;
	float mapZ = (float)mapSize.second;

	for (float x = 0.0f; x < mapX; x++) {
		for (float z = 0.0f; z < mapZ; z++) {
			_matrices.find("floor")->second = glm::translate(glm::mat4(), glm::vec3((x * 2.0), -0.5f, (-1 * z) * 2)); 
			_models.find("floor")->second->render(_matrices.find("floor")->second, view, projection);
		
		}
	}

	_shaders.find("wall")->second->enable();
	std::vector<UnbreakableBox> tempUB = _game->getUnbreakableBs();
	vecSize = tempUB.size();
	std::cout << "Doing " << vecSize << " Unbreakable Boxes." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempUB[i].getXY();
		std::cout << "UBcoords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_matrices.find("wall")->second = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2))); 
		_models.find("wall")->second->render(_matrices.find("wall")->second, view, projection);
	}
	
	_shaders.find("box")->second->enable();
	std::vector<BreakableBox> tempBB = _game->getBreakableBs();
	vecSize = tempBB.size();
	std::cout << "Doing " << vecSize << " Breakable Boxes." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempBB[i].getXY();
		std::cout << "BB coords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_matrices.find("box")->second = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2))); 
		_models.find("box")->second->render(_matrices.find("box")->second, view, projection);
	}

	/// DROPS & ENEMIES
	_shaders.find("drop")->second->enable();
	std::vector<Drop*> tempDrp = _game->getDrops();
	vecSize = tempDrp.size();
	std::cout << "Doing " << vecSize << " Drops." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempDrp[i]->getXY();
		std::cout << "coords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_matrices.find("drop")->second = glm::translate(glm::mat4(), glm::vec3(coords.first, 0.0f, (-1 * coords.second))); 
		_models.find("drop")->second->render(_matrices.find("drop")->second, view, projection);
	}

/*
	_shaders.find("enemy")->second->enable();
	std::vector<Enemy> tempEnmy = _game->getEnemies();
	vecSize = tempEnmy.size();
	std::cout << "Doing " << vecSize << " Enemies." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempEnmy[i].getXY();
		std::cout << "ENEMYcoords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_matrices.find("enemy")->second = glm::translate(glm::mat4(), glm::vec3(coords.first, 0.0f, (-1 * coords.second))); 
		_models.find("enemy")->second->render(_matrices.find("enemy")->second, view, projection);
	}
*/
	glfwSwapBuffers(_window);
}

// getters

Game								*GraphicsEngine::getGame() const {
	return this->_game;
}

GLFWwindow							*GraphicsEngine::getWindow() const {
	return this->_window;
}

Camera								*GraphicsEngine::getCamera() const {
	return this->_camera;
}

std::map<std::string, Shader*>		GraphicsEngine::getShaders() const {
	return this->_shaders;
}

std::map<std::string, Model*>		GraphicsEngine::getModels() const {
	return this->_models;
}

std::map<std::string, glm::mat4>	GraphicsEngine::getMatrices() const {
	return this->_matrices;
}

// setters

void	GraphicsEngine::setGame(Game *game) {
	this->_game = game;
}

void	GraphicsEngine::setWindow(GLFWwindow *window) {
	this->_window = window;
}

void	GraphicsEngine::setCamera(Camera camera) {
	this->_camera = &camera;
}

void	GraphicsEngine::setShaders(std::map<std::string, Shader*> shaders) {
	this->_shaders = shaders;
}

void	GraphicsEngine::setModels(std::map<std::string, Model*> models) {
	this->_models = models;
}

void	GraphicsEngine::setMatrices(std::map<std::string, glm::mat4> matrices) {
	this->_matrices = matrices;
}

