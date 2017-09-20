#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../gfxUtils/glm/glm.hpp"
#include "../gfxUtils/glm/gtc/type_ptr.hpp"
#include "../gfxUtils/glm/gtc/matrix_transform.hpp"

//#include "Game.hpp"
#include "Camera.hpp"
//#include "Shader.hpp"
#include "Shader.hpp"
//#include "Model.hpp"
#include "tiny_gltf.h"
#include "stb_image.h"
#include "picojson.h"
#include "util.h"

#include <iostream>
/*
class GraphicsEngine {
	private:
	Camera							*_camera;
	Shader2							*_shader;
	std::map<std::string, Model*>	_models;
	Game							*_game;
	GLFWwindow						*_window;

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
		bool	processInput();
		void	render();
};
*/
