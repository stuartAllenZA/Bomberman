#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <type_ptr.hpp>
#include <matrix_transform.hpp>

#include "Game.hpp"
#include "Camera.hpp"
#include "ModelShader.hpp"
#include "Model.hpp"
#include "tiny_gltf.h"
#include "stb_image.h"
#include "picojson.h"
#include "Util.hpp"

class GraphicsEngine {
	private:
		Camera								*_camera;
		Shader								*_playerShader;
		Shader								*_wallShader;
		Shader								*_boxShader;
		Shader								*_enemyShader;
		Shader								*_bombShader;
		std::map<std::string, Model*>		_models;
		std::map<std::string, Shader>		_shaders;
		std::map<std::string, glm::mat4>	_matrices;
		Model								*_playerModel;
		Model								*_wallModel;
		Material 							_playerMaterial;
		Game								*_game;
		GLFWwindow							*_window;
		float								_prevZ;
		float								_prevX;

		void								_loadResources();
		void								_loadModels();
		void								_loadModel();

	public:
		GraphicsEngine(Game	*game, GLFWwindow **window);
		GraphicsEngine(GLFWwindow **window);
		GraphicsEngine(GLFWwindow *window);
		GraphicsEngine(GraphicsEngine const & src);
		GraphicsEngine	&operator=(GraphicsEngine const & src);
		GraphicsEngine();
		~GraphicsEngine();
		void	init();
		void	initSystems();
		bool	processInput();
		void	render();

		// getters
		
		Game								*getGame() const;
		GLFWwindow							*getWindow() const;
		Camera								*getCamera() const;
		std::map<std::string, Shader>		getShaders() const;
		std::map<std::string, Model*>		getModels() const;
		std::map<std::string, glm::mat4>	getMatrices() const;

		// setters

		void	setGame(Game *);
		void	setWindow(GLFWwindow *);
		void	setCamera(Camera);
		void	setShaders(std::map<std::string, Shader>);
		void	setModels(std::map<std::string, Model*>);
		void	setMatrices(std::map<std::string, glm::mat4>);
};
