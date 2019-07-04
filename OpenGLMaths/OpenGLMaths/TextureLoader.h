#pragma once

#define GLEW_STATIC 1
#define STB_IMAGE_IMPLEMENTATION

#include <stdlib.h>
#include <glew.h>
#include <glfw3.h>

#include "GLShader.h"

GLuint LoadAndCreateTextureRGBA(const char *filename);