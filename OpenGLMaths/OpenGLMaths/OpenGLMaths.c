// Rotation.c : définit le point d'entrée pour l'application console.
//

// comme on link avec glew32s.lib (en static)
// il faut forcer les bons includes egalement
#define GLEW_STATIC 1	
#include <glew.h>

#include <glfw3.h>

#include "GLShader.h"
#include <math.h>

int main(void)
{
	GLFWwindow* window;
	GLint width = 800;
	GLint height = 600;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "OpenGLMaths", NULL, NULL);
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
		glVertexAttribPointer(canalColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), cube_vertices);
		glEnableVertexAttribArray(canalColor);

		float time = (float)glfwGetTime();
		GLint locTime = glGetUniformLocation(CubeProgram, "u_Time");
		glUniform1f(locTime, time);

		//Matrice de rotation
		float rotationMatrix[9] = 
		{
			1, 0, 0,
			0, cos(time), -sin(time),
			0, sin(time), cos(time)
		};

		GLint matLoc = glGetUniformLocation(CubeProgram, "rotationMatrix");
		glUniformMatrix3fv(matLoc, 1, GL_FALSE, rotationMatrix);

		float identityMatrix[9] = {
			cos(time), -sin(time), 0,
			sin(time), cos(time), 0,
			0, 0, 1

		};

		matLoc = glGetUniformLocation(CubeProgram, "identityMatrix");
		glUniformMatrix3fv(matLoc, 1, GL_FALSE, identityMatrix);

		// alternativement on peut modifier le "point size"
		// dans le shader avec la variable gl_PointSize
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