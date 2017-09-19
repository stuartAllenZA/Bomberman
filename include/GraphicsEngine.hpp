#pragma once

#include <GL/glew.h>
#include "glfw3.h"
#include "../gfxUtils/glm/glm.hpp"
#include "../gfxUtils/glm/gtc/type_ptr.hpp"

#include "camera.hpp"
#include "Game.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "tiny_gltf.h"
#include "stb_image.h"
#include "picojson.h"
#include "util.h"

class GraphicsEngine {
	private:
	Camera							*_camera;
	Shader							*_shader;
	std::map<std::string, Model*>	_models;
	Game							*_game;
	GLFWwindow						*_window;
	float	_deltaTime;

	void	_loadResources();
	void	_loadModels();
	void	_loadModel();

	public:
		GraphicsEngine(Game	*game, GLFWwindow **window);
		GraphicsEngine();
		GraphicsEngine(GLFWwindow **window);
		GraphicsEngine(GLFWwindow *window);
		~GraphicsEngine();
		void	init();
		void	initSystems();
		void	render();
		void	framebuffer_size_callback(int width, int height);
		void	mouse_callback(double xpos, double ypos);
		void	scroll_callback(double xoffset, double yoffset);
		bool	processInput();

};
