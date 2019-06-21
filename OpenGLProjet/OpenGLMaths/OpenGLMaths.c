#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "..\common\GLShader.h"

void main()
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewInit();

	//appel des shaders
	GLShader test;
	CreateProgram(&test);
	LoadVertexShader(test, "test.vs.glsl.txt");
	LoadFragmentShader(test, "test.fs.glsl.txt");
	LinkProgram(test);

	GLShader testOffset;
	CreateProgram(&testOffset);
	LoadVertexShader(testOffset, "testOffset.vs.glsl.txt");
	LoadFragmentShader(testOffset, "test.fs.glsl.txt");
	LinkProgram(testOffset);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		//backface culling ==> face cachée sont en antihoraire par défaut 
		glEnable(GL_CULL_FACE);
		//on indique que les faces avants sont définies dans le sens horaire =/= GL_CCW
		glFrontFace(GL_CW);

		static const float triangleFat[] = {
			0.0f, 0.5f, 1.0f, 1.0f, 0.0f,
			0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.5f, 1.0f
		};

		//------------------------Premier triangle------------------------------------------
		//récupère la variable a_Position et retourne le numéro du canal
		GLint canalPos = glGetAttribLocation(test._Program, "a_Position");
		glVertexAttribPointer(canalPos, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), triangleFat);
		glEnableVertexAttribArray(canalPos);

		//récupère la variable a_Color et retourne le numéro du canal
		GLint canalColor = glGetAttribLocation(test._Program, "a_Color");
		glVertexAttribPointer(canalColor, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), triangleFat + 2);
		glEnableVertexAttribArray(canalColor);

		glUseProgram(test._Program);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//------------------------Offset du triangle------------------------------------------
		glUseProgram(testOffset._Program);

		GLint canalPosOffset = glGetAttribLocation(testOffset._Program, "a_Position");
		glVertexAttribPointer(canalPosOffset, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), triangleFat);
		glEnableVertexAttribArray(canalPosOffset);

		glVertexAttribPointer(canalColor, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), triangleFat + 2);
		glEnableVertexAttribArray(canalColor);

		//animer le triangle en passant le temps comme variable uniform == constante pendant un appel au glDraw
		float time = (float)glfwGetTime();
		//on doit récupérer l'identifiant(le canal location) de la variable uniform
		GLint locTime = glGetUniformLocation(testOffset._Program, "u_Time");
		//ATTENTION uniform doit correspondre à la valeur qu'on fait passer en paramètres
		glUniform1f(locTime, time);


		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	DestroyProgram(&test);
	DestroyProgram(&testOffset);

	glfwTerminate();
	return 0;
}