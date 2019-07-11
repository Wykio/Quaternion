// Rotation.c�: d�finit le point d'entr�e pour l'application console.
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
#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>

#include "Quaternions.h"
#include "Matrix4.h"
#include "Vec3.h"

#include "ObjImporter.h"
#include "TextureLoader.h"
#include "Input.h"

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

	//Cr�ation du programme
	GLShader CubeShader;
	CreateProgram(&CubeShader);
	LoadVertexShader(CubeShader, "Cube.vs.glsl");
	LoadFragmentShader(CubeShader, "Cube.fs.glsl");
	LinkProgram(CubeShader);
	GLuint CubeProgram = CubeShader._Program;
	glUseProgram(CubeProgram);

	//load obj
	std::vector< float > vertices;
	std::vector< float > uvs;
	std::vector< float > normals;
	std::vector< unsigned int > indices;
	bool res = loadObj("teapot.obj", vertices, uvs, normals, indices);

	//Texture
	GLuint texture = LoadAndCreateTextureRGBA("../Textures/benjamin_raynal.jpg");
	GLint locTexture = glGetUniformLocation(CubeProgram, "u_Texture");
	glUniform1f(locTexture, texture);

	//Inputs
	Input input = Input();
	input.lastTime = glfwGetTime();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Attributes
	GLint canalPos = glGetAttribLocation(CubeProgram, "a_Position");
	glVertexAttribPointer(canalPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), &vertices[0]);
	glEnableVertexAttribArray(canalPos);

	GLint canalUV = glGetAttribLocation(CubeProgram, "a_Uv");
	glVertexAttribPointer(canalUV, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), &uvs[0]);
	glEnableVertexAttribArray(canalUV);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapInterval(0);

		//Temps
		float time = (float)glfwGetTime();
		GLint locTime = glGetUniformLocation(CubeProgram, "u_Time");
		glUniform1f(locTime, time);

		//----------------Matrix-----------------------------
		input.computeMatricesFromInputs(window, windowWidth, windowHeight);

		//-----------------Model matrix----------------------------
		//ATTENTION LES MATRICES C'EST EN VERTICAL
		
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
			0, cos(time), sin(time), 0,
			0, -sin(time), cos(time), 0,
			0, 0, 0, 1
		);

		//Scale
		Matrix4 scaleMatrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);

		Matrix4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix ;

		GLint modelLoc = glGetUniformLocation(CubeProgram, "modelMatrix");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMatrix.m);

		//-----------------------View matrix------------------------------

		//Position de la cam�ra
		/*Vec3 eye = {
		0, 0, -1
		};

		//Centre de l'objet regard�
		Vec3 center = {
			0, 0, 0
		};*/

		//Matrix4 viewMatrix = Matrix4::lookAt(eye, center, Vec3(0, 1, 0));

		glm::mat4 view = input.getViewMatrix();
		GLint viewLoc = glGetUniformLocation(CubeProgram, "viewMatrix");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);


		//------------------------Projection matrix-------------------------------

		/*float fov = 45 * (3.14 / 180);
		float aspectRatio = (float)windowWidth / (float)windowHeight;
		float nearClipPlane = 0.01f;
		float farClipPlane = 1000.f;

		Matrix4 projectionMatrix = Matrix4::perspective(fov, aspectRatio, nearClipPlane, farClipPlane);*/
		glm::mat4 projection = input.getProjectionMatrix();
		GLint projectionLoc = glGetUniformLocation(CubeProgram, "projectionMatrix");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

		//Draw
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteTextures(1, &texture);

	DestroyProgram(&CubeShader);

	glfwTerminate();
	return 0;
}