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

	std::vector< float > vertices2;
	std::vector< float > uvs2;
	std::vector< float > normals2;
	std::vector< unsigned int > indices2;

	std::vector< float > vertices3;
	std::vector< float > uvs3;
	std::vector< float > normals3;
	std::vector< unsigned int > indices3;

	bool res = loadObj("teapot.obj", vertices, uvs, normals, indices);
	bool res2 = loadObj("models/scene.obj", vertices2, uvs2, normals2, indices2);
	//bool res3 = loadObj("cube.obj", vertices3, uvs3, normals3, indices3);

	//Inputs
	Input input = Input();
	input.lastTime = glfwGetTime();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	GLuint texture; 
	GLint locTexture = glGetUniformLocation(CubeProgram, "u_Texture");
	GLuint textureParquet = LoadAndCreateTextureRGBA("../Textures/Parquet.jpg");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapInterval(0);
		//Temps
		float time = (float)glfwGetTime();

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

		//Scale
		Matrix4 scaleMatrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);

		//------------------------------------Quaternions---------------------------
		//déclaration d'un quaternions
		Quaternions quater = Quaternions(1, 1, 1, 1);
		quater = quater.Location(quater, input.rotation, 1 * time);

		//matrix de rotation de quater
		Matrix4 quaternionMatrix = quater.rotationMatrix(quater);
		//récréation de model matrix
		Matrix4 modelMatrix = translationMatrix * quaternionMatrix * scaleMatrix;

		GLint quaterLoc = glGetUniformLocation(CubeProgram, "modelMatrix");
		glUniformMatrix4fv(quaterLoc, 1, GL_FALSE, modelMatrix.m);

		//-----------------------View matrix------------------------------

		glm::mat4 view = input.getViewMatrix();
		GLint viewLoc = glGetUniformLocation(CubeProgram, "viewMatrix");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		//------------------------Projection matrix-------------------------------
		
		glm::mat4 projection = input.getProjectionMatrix();
		GLint projectionLoc = glGetUniformLocation(CubeProgram, "projectionMatrix");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);


		//-------------------------Premier OBJ---------------------------------
		//Texture
		texture = LoadAndCreateTextureRGBA("../Textures/Debug.jpg");
		glUniform1f(locTexture, texture);

		// Attributes
		//Position
		GLint canalPos = glGetAttribLocation(CubeProgram, "a_Position");
		glVertexAttribPointer(canalPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), &vertices[0]);
		glEnableVertexAttribArray(canalPos);

		//UV
		GLint canalUV = glGetAttribLocation(CubeProgram, "a_Uv");
		glVertexAttribPointer(canalUV, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), &uvs[0]);
		glEnableVertexAttribArray(canalUV);

		//Draw
		glDrawArrays(GL_TRIANGLES, 0, indices.size());

		//-------------------------Deuxième OBJ----------------------------------
		//Texture
		texture = LoadAndCreateTextureRGBA("../Textures/Parquet.jpg");
		glUniform1f(locTexture, texture);

		// Attributes
		//Position
		glVertexAttribPointer(canalPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), &vertices2[0]);
		glEnableVertexAttribArray(canalPos);

		//UV
		glVertexAttribPointer(canalUV, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), &uvs2[0]);
		glEnableVertexAttribArray(canalUV);

		glUniformMatrix4fv(quaterLoc, 1, GL_FALSE, Matrix4().m);

		//Draw
		glDrawArrays(GL_TRIANGLES, 0, indices2.size());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &textureParquet);
	DestroyProgram(&CubeShader);

	glfwTerminate();
	return 0;
}