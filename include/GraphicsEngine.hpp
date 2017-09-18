#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "../gfxUtils/glm/glm.hpp"
#include "../gfxUtils/glm/gtc/matrix_transform.hpp"
#include "../gfxUtils/glm/gtc/type_ptr.hpp"

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

int	GraphicsEngineInit();
/*
class GraphicsEngine {
	private:

	public:
		GraphicsEngine();
		~GraphicsEngine();
		GraphicsEngine(GraphicsEngine const &src);
		GraphicsEngine &operator=(GraphicsEngine const &src);
		int		init();
		void	render();
};
*/
