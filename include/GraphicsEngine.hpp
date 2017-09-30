#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <type_ptr.hpp>
#include <matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


#include "Game.hpp"
#include "Camera.hpp"
#include "ModelShader.hpp"
#include "Model.hpp"
#include "tiny_gltf.h"
#include "stb_image.h"
#include "picojson.h"
#include "Util.hpp"
#include "../common/shader.hpp"
#include "../common/texture.hpp"
#include "../common/controls.hpp"
#include "../common/objloader.hpp"
#include "../common/vboindexer.hpp"
#include "../common/text2D.hpp"

#define GLM_FORCE_RADIANS

class GraphicsEngine {
	private:
		Camera								_camera;
		Shader								*_playerShader;
		Shader								*_wallShader;
		Shader								*_floorShader;
		Shader								*_boxShader;
		Shader								*_bombShader;
		Shader								*_flameShader;
		Shader								*_enemyShader;
		Shader								*_dropShader;
		
		Model								*_playerModel;
		Model								*_wallModel;
		Model								*_floorModel;
		Model								*_boxModel;
		Model								*_bombModel;
		Model								*_flameModel;
		Model								*_enemyModel;
		Model								*_dropModel;

		glm::mat4							_playerMatrice;
		glm::mat4							_wallMatrice;
		glm::mat4							_floorMatrice;
		glm::mat4							_boxMatrice;
		glm::mat4							_bombMatrice;
		glm::mat4							_flameMatrice;
		glm::mat4							_enemyMatrice;
		glm::mat4							_dropMatrice;

		Game								*_game;
		GLFWwindow							*_window;
		float								_prevZ;
		float								_prevX;
		float								_playerRotate;
		bool								_isAnime;

		void								_loadResources();
		void								_loadModels();
		void								_loadModel();
		bool								_cameraLoaded;

	public:
		GraphicsEngine(Game	*game, GLFWwindow **window);
		GraphicsEngine(GLFWwindow **window);
		GraphicsEngine(GLFWwindow *window);
		GraphicsEngine(GraphicsEngine const & src);
		GraphicsEngine	&operator=(GraphicsEngine const & src);
		GraphicsEngine();
		~GraphicsEngine();
		void	init();
		void	initCamera();
		void	initSystems();
		bool	processInput();
		void	render();
		void	renderText();

		// getters
		
		Game								*getGame() const;
		GLFWwindow							*getWindow() const;
		Camera								getCamera() const;
		Shader								*getPlayerShader() const;
		Shader								*getWallShader() const;
		Shader								*getFloorShader() const;
		Shader								*getBoxShader() const;
		Shader								*getBombShader() const;
		Shader								*getFlameShader() const;
		Shader								*getEnemyShader() const;
		Shader								*getDropShader() const;

		Model								*getPlayerModel() const;
		Model								*getWallModel() const;
		Model								*getFloorModel() const;
		Model								*getBoxModel() const;
		Model								*getBombModel() const;
		Model								*getFlameModel() const;
		Model								*getEnemyModel() const;
		Model								*getDropModel() const;

		// setters

		void	setGame(Game *);
		void	setWindow(GLFWwindow *);
		void	setCamera(Camera);
		void	setShaders(std::map<std::string, Shader*>);
		void	setModels(std::map<std::string, Model*>);
		void	setMatrices(std::map<std::string, glm::mat4>);
};
