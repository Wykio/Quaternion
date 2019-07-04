// Rotation.c : définit le point d'entrée pour l'application console.
//

// comme on link avec glew32s.lib (en static)
// il faut forcer les bons includes egalement
//#pragma once
#define GLEW_STATIC 1	
#include <glew.h>

#include <glfw3.h>

#include "GLShader.h"
#include <math.h>
#include <iostream>

#include "Matrix4.h"
#include "Vec3.h"


int main(void)
{
	GLFWwindow* window;
	GLint windowWidth = 800;
	GLint windowHeight = 600;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowWidth, windowHeight, "OpenGLMaths", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// INITIALISATION
	glewInit();

	GLShader CubeShader;
	CreateProgram(&CubeShader);
	LoadVertexShader(CubeShader, "Cube.vs.glsl");
	LoadFragmentShader(CubeShader, "Cube.fs.glsl");
	LinkProgram(CubeShader);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_CULL_FACE);


		const GLfloat cube_vertices[] = 
		{ // front 
			-0.5, -0.5, 0.5, 1.0, 0.0, 0.0,
			0.5, -0.5, 0.5, 1.0, 1.0, 1.0,
			0.5, 0.5, 0.5, 0.0, 0.0, 1.0,
			-0.5, 0.5, 0.5, 1.0, 1.0, 0.0,
			// back
			-0.5, -0.5, -0.5, 1.0, 0.5, 0.0,
			0.5, -0.5, -0.5, 0.0, 1.0, 0.0,
			0.5, 0.5, -0.5, 1.0, 0.5, 0.0,
			-0.5, 0.5, -0.5, 0.0, 1.0, 0.5
		};

		const GLushort cube_elements[] =
		{
			// front
			0, 1, 2, 2, 3, 0,
			// right
			1, 5, 6, 6, 2, 1,
			// back
			7, 6, 5, 5, 4, 7,
			// left
			4, 0, 3, 3, 7, 4,
			// bottom
			4, 5, 1, 1, 0, 4,
			// top
			3, 2, 6,6, 7, 3
		};

		// glUseProgram rend un programme actif
		// une valeur de '0' remet le programme par defaut
		GLuint CubeProgram = CubeShader._Program;
		glUseProgram(CubeProgram);

		GLint canalPos = glGetAttribLocation(CubeProgram, "a_Position");
		glVertexAttribPointer(canalPos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), cube_vertices);
		glEnableVertexAttribArray(canalPos);

		GLint canalColor = glGetAttribLocation(CubeProgram, "a_Color");
		glVertexAttribPointer(canalColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), cube_vertices + 3);
		glEnableVertexAttribArray(canalColor);

		float time = (float)glfwGetTime();
		GLint locTime = glGetUniformLocation(CubeProgram, "u_Time");
		glUniform1f(locTime, time);


		//Model matrix

		//Translation
		Matrix4 translationMatrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);

		//Rotation
		Matrix4 rotationMatrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);

		//Scale
		Matrix4 scaleMatrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);

		Matrix4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

		GLint modelLoc = glGetUniformLocation(CubeProgram, "modelMatrix");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMatrix.m);


		//View matrix

		//Position de la caméra
		Vec3 eye = {
			0, 0, -1
		};

		//Centre de l'objet regardé
		Vec3 center = {
			0, 0, 0
		};
		
		Matrix4 viewMatrix = Matrix4::lookAt(eye, center, Vec3(0, 1, 0));

		GLint viewLoc = glGetUniformLocation(CubeProgram, "viewMatrix");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewMatrix.m);


		//Projection matrix

		float fov = 90 * 3.14 / 180;
		float aspectRatio = (float)windowWidth / (float)windowHeight;
		float nearClipPlane = 0.1f;
		float farClipPlane = 100.f;

		//Matrice de rotation
		Matrix4 projectionMatrix = Matrix4::perspective(fov, aspectRatio, nearClipPlane, farClipPlane);

		GLint projectionLoc = glGetUniformLocation(CubeProgram, "projectionMatrix");
		glUniformMatrix3fv(projectionLoc, 1, GL_FALSE, projectionMatrix.m);


		//Draw
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, cube_elements);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	DestroyProgram(&CubeShader);

	glfwTerminate();
	return 0;
}