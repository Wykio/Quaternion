#pragma once
#define GLEW_STATIC 1	
#include <glew.h>

#include <glfw3.h>

#include "GLShader.h"
#include <math.h>

#include "ObjImporter.h"

GLuint obj;
float rotation;
char ch = '1';

void loadOBJ(const char *objName)
{
	FILE *fp;
	int read;
	GLfloat x, y, z;
	char ch;
	obj = glGenLists(1);
	//tableau des vertexs
	//static float vertices[1000000];

	//TODO : test avec des vectors
	std::vector<float> tempVertices;
	std::vector<float> tempUvs;
	std::vector<float>tempNormals;

	fp = fopen(objName, "r");
	if (!fp)
	{
		printf("can't open file %s\n", objName);
		exit(1);
	}

	//glPointSize(2.0);
	glNewList(obj, GL_COMPILE);
	{
		glPushMatrix();
		//glBegin(GL_POINTS);

		while (!(feof(fp)))
		{
			read = fscanf(fp, "%s", &ch);
			if (ch == "v")
			{
				fscanf(file, "%f, %f, %f\n", &x, &y, &z);
				tempVertices.push_back(x, y, z);
			}
			//read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			//TODO : essayer avec un scan de toute la ligne + split ligne
			/*if (read == 4 && ch == 'v')
			{
				glVertex3f(x, y, z);
			}*/
		}
		glEnd();
	}

	glPopMatrix();
	glEndList();
	fclose(fp);
}
/*
void createShape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void drawObj()
{
	glPushMatrix();
	glTranslatef(0, -40.00, -105);
	glColor3f(1.0, 0.23, 0.27);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(rotation, 0, 1, 0);
	glCallList(obj);
	glPopMatrix();
	rotation = rotation + 0.6;
	if (rotation > 360)rotation = rotation - 360;
}
*/
