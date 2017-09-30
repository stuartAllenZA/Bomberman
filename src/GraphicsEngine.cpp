#include <GraphicsEngine.hpp>
#include <Model.hpp>

GLFWwindow* window;
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

	_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (_window == NULL)
	{
		//std::cout << "Failed to create GLFW window" << std::endl;
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
	_enemyShader = new Shader("resources/shaders/anime.vert", "resources/shaders/basic.frag");

	// init models
	_playerModel = new Model("resources/models/BMwalk3.gltf", _playerShader);
	_wallModel = new Model("resources/models/Cube.gltf", _wallShader);
	_floorModel = new Model("resources/models/BMfloor.gltf", _floorShader);
	_boxModel = new Model("resources/models/block1.gltf", _boxShader);
	_bombModel = new Model("resources/models/BMbomb.gltf", _bombShader);
	_flameModel = new Model("resources/models/BMextraflame.gltf", _flameShader);
	_enemyModel = new Model("resources/models/boneBox.gltf", _enemyShader);
	_dropModel = new Model("resources/models/boneBox.gltf", _dropShader);
	
	// load init positions
	std::pair<float, float> coords;
	coords = _game->getPlayer().getXY();
	_playerMatrice = glm::translate(glm::mat4(), glm::vec3(coords.first * 2.0f, 0.0f, coords.second * 2.0f)); 
	_wallMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_boxMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_bombMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_flameMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_floorMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_enemyMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	_dropMatrice = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); 
	
}

void	GraphicsEngine::renderText() {
	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 11 - 2D Fonts", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture
	GLuint Texture = loadDDS("uvmap.DDS");
	
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	loadOBJ("suzanne.obj", vertices, uvs, normals);

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	// Initialize our little text library with the Holstein font
	initText2D( "Holstein.DDS" );

	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	do{

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0/double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
	//	computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(4,4,4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_SHORT, // type
			(void*)0           // element array buffer offset
		);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		char text[256];
		sprintf(text,"%.2f sec", glfwGetTime() );
		printText2D(text, 10, 500, 60);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO, shader and texture
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Delete the text's VBO, the shader and the texture
	cleanupText2D();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();


}

void GraphicsEngine::render() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
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
	////
	glm::vec4 myPosition(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 rotationAxis(0.0f, 1.0f, 0.0f);
	glm::mat4 scalar = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
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
	//std::cout << "Doing " << vecSize << " Drops." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = bombs[i].getXY();
		std::cout << "coords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_bombMatrice = glm::translate(glm::mat4(), glm::vec3(coords.first * 2.0f, 0.0f, (-1 * coords.second * 2.0f))); 
		_bombModel->render(_bombMatrice, view, projection);
	}
	std::vector<Flame> flames= _game->getFlames();
	vecSize = flames.size();
	//std::cout << "Doing " << vecSize << " Drops." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = flames[i].getXY();
		std::cout << "coords x: " << coords.first << " coords y: " << coords.second << std::endl;
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
	//std::cout << "Doing " << vecSize << " Unbreakable Boxes." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempUB[i].getXY();
		//std::cout << "UBcoords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_wallMatrice = glm::translate(glm::mat4(), glm::vec3((coords.first * 2.0), 0.0f, ((-1 * coords.second) * 2))); 
		_wallModel->render(_wallMatrice, view, projection);
	}
	
	_boxShader->enable();
	std::vector<BreakableBox> tempBB = _game->getBreakableBs();
	vecSize = tempBB.size();
	//std::cout << "Doing " << vecSize << " Breakable Boxes." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempBB[i].getXY();
		//std::cout << "BB coords x: " << coords.first << " coords y: " << coords.second << std::endl;
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
		_dropMatrice = glm::translate(glm::mat4(), glm::vec3(coords.first, 0.0f, (-1 * coords.second))); 
		_dropModel->render(_dropMatrice, view, projection);
	}
	_enemyShader->enable();
	std::vector<Enemy> tempEnmy = _game->getEnemies();
	vecSize = tempEnmy.size();
	//std::cout << "Doing " << vecSize << " Enemies." << std::endl;
	for (int i = 0; i < vecSize; i++) {
		coords = tempEnmy[i].getXY();
		//std::cout << "ENEMYcoords x: " << coords.first << " coords y: " << coords.second << std::endl;
		_enemyMatrice = glm::translate(glm::mat4(), glm::vec3(coords.first, 0.0f, (-1 * coords.second))); 
		_enemyModel->render(_enemyMatrice, view, projection);
	}
	printText2D("text here", 10, 500, 60);
	glfwSwapBuffers(_window);
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

