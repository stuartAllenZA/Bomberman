#include <GraphicsEngine.hpp>

// GLOBAL test state modifiers
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

float deltaTime = 0.0f;	
float lastFrame = 0.0f;
// #endif GLOBAL test state modifiers


GraphicsEngine::GraphicsEngine() {
	std::cout << "graphics engine constructed\n";
}

GraphicsEngine::GraphicsEngine(Game *game, GLFWwindow **window) : _window(*window), _game(game) {
	std::cout << "graphics engine constructed\n";
}

GraphicsEngine::GraphicsEngine(GLFWwindow **window) : _window(*window) {
	std::cout << "graphics engine constructed\n";
}

GraphicsEngine::GraphicsEngine(GLFWwindow *window) : _window(window) {
	std::cout << "graphics engine constructed\n";
}

GraphicsEngine::~GraphicsEngine() {
	std::cout << "graphics engine destructed\n";
}

// external loader - external from Core
void	GraphicsEngine::initSystems() {
	std::cout << "creating glfw window" << std::endl;
	glfwInit();
	glfwSetTime(0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	_window = glfwCreateWindow(1920, 1280, "Bomberman", nullptr, nullptr);
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
	}
	glEnable(GL_DEPTH_TEST);
}

void	GraphicsEngine::init() {
	std::cout << "inititializing graphics engine\n";
	_shader = new Shader("GraphicsEngine/shaders/basic.vert", "GraphicsEngine/shaders/basic.frag");	
	_loadResources();
}

void	GraphicsEngine::_loadResources() {
	std::cout << "loading graphics resources\n";
	_loadModels();
}

void	GraphicsEngine::_loadModels() {
	_loadModel();	
}

void	GraphicsEngine::_loadModel() {
	_models["bomberman"] = new Model("resources/models/bomberman.gltf");
}

void	GraphicsEngine::render() {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glClearColor(0.5f, 0.1f, 0.1f, 0.8f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		_shader->enable();
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::vec3 viewPos = glm::vec3(0.0f, 1.0f, -1.0f);
		_shader->setUniformMat4((GLchar *)"proj_matrix", projectionMatrix);
		_shader->setUniformMat4((GLchar *)"view_matrix", viewMatrix);
		_shader->setUniform3f((GLchar *)"viewPos", viewPos);
		_shader->disable();
		auto search = _models.find("bomberman");
		if (search != _models.end()) {
			std::cout << "Found " << search->first << " " << search->second << std::endl;
			search->second->render(search->second->mat);
		}
		else { std::cout << "Bomberman renderable not found\n"; }
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

bool GraphicsEngine::processInput()
{
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		return true;

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	return false;
}

void GraphicsEngine::framebuffer_size_callback(int width, int height)
{
	glViewport(0, 0, width, height);
}

void GraphicsEngine::mouse_callback(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void GraphicsEngine::scroll_callback(double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}
