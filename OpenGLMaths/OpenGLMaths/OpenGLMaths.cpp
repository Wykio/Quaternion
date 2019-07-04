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

#include "Quaternions.h"
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

	//Cube coordonnées
	const GLfloat cube_vertices[] =
	{   // Positions           // Couleurs
		//Face avant    
		-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f, //inf gauche rouge
		 0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f, //inf droit  vert
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f, //sup droit  jaune
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f, //sup gauche bleu
		//Face arrière    
		-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f, //inf gauche magenta
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f, //inf droit  cyan
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f, //sup droit  blanc 
		-0.5f,  0.5f, -0.5f,   0.5f, 0.5f, 0.5f  //sup gauche gris
	};

	//Cube indices
	const GLushort cube_elements[] =
	{
		//Face avant    
		0, 1, 3,  3, 1, 2,
		//Face droite
		2, 1, 5,  2, 5, 6,
		//Face arrière
		6, 5, 4,  6, 4, 7,
		//Face gauche
		7, 4, 0,  7, 0, 3,
		//Face haut
		3, 2, 7,  7, 2, 6,
		//Face bas
		4, 5, 0,  0, 5, 1
	};

	//Création du programme
	GLShader CubeShader;
	CreateProgram(&CubeShader);
	LoadVertexShader(CubeShader, "Cube.vs.glsl");
	LoadFragmentShader(CubeShader, "Cube.fs.glsl");
	LinkProgram(CubeShader);
	GLuint CubeProgram = CubeShader._Program;
	glUseProgram(CubeProgram);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glEnable(GL_CULL_FACE); 
		
		// Attributes
		GLint canalPos = glGetAttribLocation(CubeProgram, "a_Position");
		glVertexAttribPointer(canalPos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), cube_vertices);
		glEnableVertexAttribArray(canalPos);

		GLint canalColor = glGetAttribLocation(CubeProgram, "a_Color");
		glVertexAttribPointer(canalColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), cube_vertices + 3);
		glEnableVertexAttribArray(canalColor);

		//Temps
		float time = (float)glfwGetTime();
		GLint locTime = glGetUniformLocation(CubeProgram, "u_Time");
		glUniform1f(locTime, time);

		//-----------------Model matrix----------------------------
		//ATTENTION LES MATRICES C'EST EN VERTICAL
		//Translation
		Matrix4 translationMatrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, -0.5, 1
		);

		//Rotation
		Matrix4 rotationMatrix(
			1, 0, 0, 0,
			0,cos(time), sin(time), 0,
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

		Matrix4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

		GLint modelLoc = glGetUniformLocation(CubeProgram, "modelMatrix");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMatrix.m);

		//-----------------------View matrix------------------------------

		//Position de la caméra
		Vec3 eye = {
		0, 0, -1
		};

		//Centre de l'objet regardé
		Vec3 center = {
			0, 0, 0
		};

		Matrix4 viewMatrix = Matrix4::lookAt(eye, center, Vec3(0, -1, 0));

		GLint viewLoc = glGetUniformLocation(CubeProgram, "viewMatrix");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewMatrix.m);


		//------------------------Projection matrix-------------------------------

		float fov = 90 * 3.14 / 180;
		float aspectRatio = (float)windowWidth / (float)windowHeight;
		float nearClipPlane = 0.01f;
		float farClipPlane = 1000.f;

		//Matrice de rotation
		Matrix4 projectionMatrix = Matrix4::perspective(fov, aspectRatio, nearClipPlane, farClipPlane);

		GLint projectionLoc = glGetUniformLocation(CubeProgram, "projectionMatrix");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projectionMatrix.m);

		Matrix4 test = projectionMatrix * viewMatrix * modelMatrix * Matrix4(-0.5f, -0.5f, 0.5f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

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