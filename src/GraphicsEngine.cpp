#include <GraphicsEngine.hpp>
#include <Model.hpp>

char axis = 'z';
char direction = 'n';
float z = 0.0f;
float x = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

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
	delete this->_playerModel;
	delete this->_playerShader;
	delete this->_camera;
	
	_playerModel = nullptr;
	_playerShader = nullptr;
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

void GraphicsEngine::init() {
	_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), 0, -90.0f);
	_playerShader = new Shader("shaders/anime.vert", "shaders/basic.frag");
	_wallShader = new Shader("shaders/basic.vert", "shaders/basic.frag");
	_boxShader = new Shader("shaders/basic.vert", "shaders/basic.frag");
//	_enemyShader = new Shader("shaders/anime.vert", "gfxUtils/shaders/basic.frag");

	_models["player"] = new Model("resources/models/BMrun.gltf", _playerShader);
	_models["wall"] = new Model("resources/models/Cube.gltf", _wallShader);
	_models["box"] = new Model("resources/models/block1.gltf", _boxShader);
//	_models["enemy"] = new Model("resources/models/bomberman.gltf", _enemyShader);
	
	// load init positions
	_matrices["player"] = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_matrices["wall"] = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_matrices["box"] = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
//	_matrices["enemy"] = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 

}

void GraphicsEngine::render() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	processInput();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	std::pair<float, float> coords;
	int vecSize;
/*
 *	foreach (game->object) {
 *		_matrices.find(gameobjectname)->second) = translate(game->objectCoords);
 *		render(_models.find(gameobjectname)->second);
 *	}
 */
	/*
	_enemyShader->enable();
	std::vector<Enemy> tempEnmy = _game->getEnemies();
	vecSize = tempEnmy.size();
	std::cout << "Doing " << vecSize << " Enemies." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempEnmy[i].getXY();
		std::cout << "ENEMYcoords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_matrices.find("enemy")->second = glm::translate(glm::mat4(), glm::vec3(coords.first, 0.0f, (-1 * coords.second))); 
		_models.find("enemy")->second->render(_matrices.find("enemy")->second);
	}
	*/

	_boxShader->enable();
	std::vector<BreakableBox> tempBB = _game->getBreakableBs();
	vecSize = tempBB.size();
	std::cout << "Doing " << vecSize << " Breakable Boxes." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempBB[i].getXY();
		std::cout << "BB coords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_matrices.find("box")->second = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2))); 
		_models.find("box")->second->render(_matrices.find("box")->second);
	}

	_wallShader->enable();
	std::vector<UnbreakableBox> tempUB = _game->getUnbreakableBs();
	vecSize = tempUB.size();
	std::cout << "Doing " << vecSize << " Unbreakable Boxes." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempUB[i].getXY();
		std::cout << "UBcoords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_matrices.find("wall")->second = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2))); 
		_models.find("wall")->second->render(_matrices.find("wall")->second);
	}
	/*
	std::vector<Drop*> tempDrp = _game->getDrops();
	vecSize = tempDrp.size();
	std::cout << "Doing " << vecSize << " Drops." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempUB[i]->getXY();
		std::cout << "coords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_matrices.find("wall")->second = glm::translate(glm::mat4(), glm::vec3(coords.first, 0.0f, (-1 * coords.second))); 
		_models.find("wall")->second->render(_matrices.find("wall")->second);
	}
	*/

	coords = _game->getPlayer().getXY();
	std::cout << "PLAYER coords x: " << coords.first << " coords y: " << coords.second << std::endl;
	_matrices.find("player")->second = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2))); 
	_models.find("player")->second->render(_matrices.find("player")->second);

	glfwSwapBuffers(_window);
	glfwPollEvents();
}

bool GraphicsEngine::processInput()
{
	_playerShader->enable();
	if (_game->getKeyPressArr(UP)) {
		// check direction, then rotate:
		z -= 0.1f;
//		_playerModel->render(model);
		model = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, z)); 
		axis = 'z';
		direction = 'n';
		std::cout << "w\n";
	}
	if (_game->getKeyPressArr(DOWN)) {
		if (axis == 'z' && direction == 'n')
			model = glm::rotate(model, -180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (axis == 'x' && direction == 'e')
			model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (axis == 'x' && direction == 'w')
			model = glm::rotate(model, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		z += 0.1f;
//		_playerModel->render(model);
		model = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, z)); 
		axis = 'z';
		direction = 's';
		std::cout << "s\n";
	}
	if (_game->getKeyPressArr(LEFT)) {
		if (axis == 'x' && direction == 'e')
			model = glm::rotate(model, -180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (axis == 'z' && direction == 'n')
			model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (axis == 'z' && direction == 's')
			model = glm::rotate(model, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
//		_playerModel->render(model);
		x -= 0.1f;
		model = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, z)); 
		axis = 'x';
		direction = 'w';
		std::cout << "a\n";
	}
	if (_game->getKeyPressArr(RIGHT)) {
		if (axis == 'x' && direction == 'w')
			model = glm::rotate(model, 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (axis == 'z' && direction == 'n')
			model = glm::rotate(model, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (axis == 'z' && direction == 's')
			model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
//		_playerModel->render(model);
		direction = 'e';
		model = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, z)); 
		x += 0.1f;
		axis = 'x';
		std::cout << "d\n";
	}
	return false;
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

std::map<std::string, Shader>		GraphicsEngine::getShaders() const {
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

void	GraphicsEngine::setShaders(std::map<std::string, Shader> shaders) {
	this->_shaders = shaders;
}

void	GraphicsEngine::setModels(std::map<std::string, Model*> models) {
	this->_models = models;
}

void	GraphicsEngine::setMatrices(std::map<std::string, glm::mat4> matrices) {
	this->_matrices = matrices;
}

