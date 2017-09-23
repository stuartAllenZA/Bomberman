#include <GraphicsEngine.hpp>
#include <Model.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), 0, -90.0f);
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::mat4 model;
glm::mat4 model2;
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("gfxUtils/shaders/anime.vert", "gfxUtils/shaders/basic.frag");
	Model renderable("resources/models/Cube.gltf", &ourShader);
//	Material mat;
//	mat.texure.loadTextureFromPath("resources/textures/wall.png");
//	renderable.addMaterial(0, mat);

	glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
	//ourShader.setUniformMat4((GLchar *)"proj_matrix", projection);
	float i = -0.005f;
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture1);

		ourShader.enable();

		// pass projection matrix to shader (note that in this case it could change every frame)

		// camera/view transformation
		glm::mat4 view = camera.getViewMatrix();
	//	ourShader.setUniformMat4((GLchar *)"view_matrix", view);
	//	model2 = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -i)); 
	//	model2 = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -i)); 
	//	model = glm::rotate(model, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
		// setmat4 with this external shader
/*		renderable.render(model);
		for (float i = 0.0f; i < 20.0f; i += 1.0f) {
			model = glm::translate(glm::mat4(), glm::vec3(i, 0.0f, 0.0f)); 
			renderable.render(model);
		}
		for (float i = 0.0f; i < 20.0f; i += 1.0f) {
			model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -i)); 
			renderable.render(model);
		}
		for (float i = 0.0f; i <= 20.0f; i += 1.0f) {
			model = glm::translate(glm::mat4(), glm::vec3(i, 0.0f, -20.0f)); 
			renderable.render(model);
		}
		for (float i = 0.0f; i < 20.0f; i += 1.0f) {
			model = glm::translate(glm::mat4(), glm::vec3(20.0f, 0.0f, -i)); 
			renderable.render(model);
		}
		*/
	//	i -= -0.01f;


		renderable.render(model);



	//	ourShader.setMat4("model", model);
/*		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
	//	ourShader.setMat4("model", model);
		ourShader.setUniformMat4((GLchar *)"model", model);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
*/
		//i -= 0.1f;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

float w = 0.0f;

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		// check direction, then rotate:
		// model = glm::rotate(model, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
		w -= 1.0f;
		model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, w)); 
		std::cout << "w\n";
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//		camera.ProcessKeyboard(CAM_BACKWARD, deltaTime);
		std::cout << "s\n";
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//		camera.ProcessKeyboard(CAM_LEFT, deltaTime);
		std::cout << "a\n";
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//		camera.ProcessKeyboard(CAM_RIGHT, deltaTime);
		std::cout << "d\n";
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
		glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

	//camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
}
