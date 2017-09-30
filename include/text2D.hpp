#ifndef TEXT2D_HPP
#define TEXT2D_HPP

#include <vector>
#include <cstring>

#include <GL/glew.h>

#include <glm.hpp>
#include <matrix_transform.hpp>
using namespace glm;

#include <shader.hpp>
#include <texture.hpp>

void initText2D(const char * texturePath);
void printText2D(const char * text, int x, int y, int size);
GLuint		getText2DShaderID();
void cleanupText2D();

#endif
