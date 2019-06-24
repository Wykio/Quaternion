#include "GLShader.h"
#include "glew.h"

#include <stdlib.h>
#include <stdio.h>

char* LoadSource(const char *filename)
{
	char *src = NULL;   /* code source de notre shader */
	FILE *fp = NULL;    /* fichier */
	long size;          /* taille du fichier */
	//long i;             /* compteur */


	/* on ouvre le fichier */
	fp = fopen(filename, "rb");
	/* on verifie si l'ouverture a echoue */
	if (fp == NULL)
	{
		fprintf(stderr, "impossible d'ouvrir le fichier '%s'\n", filename);
		return NULL;
	}

	/* on recupere la longueur du fichier */
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	/* on se replace au debut du fichier */
	rewind(fp);

	/* on alloue de la memoire pour y placer notre code source */
	src = malloc(size + 1); /* +1 pour le caractere de fin de chaine '\0' */
	if (src == NULL)
	{
		fclose(fp);
		fprintf(stderr, "erreur d'allocation de memoire!\n");
		return NULL;
	}

	/* lecture du fichier */
	//for (i = 0; i<size; i++)
	//	src[i] = fgetc(fp);
	fread(src, size, 1, fp);
	/* on place le dernier caractere a '\0' */
	src[size] = '\0';

	fclose(fp);

	return src;
}

uint32_t CompileShader(const char* filename, uint32_t type)
{
	GLsizei logsize = 0;
	GLint compile_status = GL_TRUE;
	char *log = NULL;

	// 1. Charger le fichier
	char* buffer = LoadSource(filename);
	if (buffer == NULL)
		return 0;

	// 2. Creer le shader objet
	uint32_t shaderObject = glCreateShader(type);
	glShaderSource(shaderObject, 1, &buffer, NULL);

	// 3. Le compiler
	glCompileShader(shaderObject);

	// 4. Nettoyer
	free(buffer);

	/* verification du succes de la compilation */
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compile_status);
	if (compile_status != GL_TRUE)
	{
		/* erreur a la compilation recuperation du log d'erreur */

		/* on recupere la taille du message d'erreur */
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &logsize);

		/* on alloue un espace memoire dans lequel OpenGL ecrira le message */
		log = malloc(logsize + 1);
		if (log == NULL)
		{
			fprintf(stderr, "impossible d'allouer de la memoire !\n");
			return 0;
		}
		/* initialisation du contenu */
		memset(log, '\0', logsize + 1);

		glGetShaderInfoLog(shaderObject, logsize, &logsize, log);
		fprintf(stderr, "impossible de compiler le shader '%s' :\n%s",
			filename, log);

		/* ne pas oublier de liberer la memoire et notre shader */
		free(log);
		glDeleteShader(shaderObject);

		return 0;
	}

	return shaderObject;
}

bool LoadVertexShader(GLShader shader, const char* filename)
{
	uint32_t vertexShader = CompileShader(filename, GL_VERTEX_SHADER);
	glAttachShader(shader._Program, vertexShader);
	glDeleteShader(vertexShader);
	return true;
}

bool LoadFragmentShader(GLShader shader, const char* filename)
{
	uint32_t fragmentShader = CompileShader(filename, GL_FRAGMENT_SHADER);
	glAttachShader(shader._Program, fragmentShader);
	glDeleteShader(fragmentShader);
	return true;
}

bool CreateProgram(GLShader* shader)
{
	shader->_Program = glCreateProgram();

	return true;
}

bool LinkProgram(GLShader shader)
{
	GLsizei logsize = 0;
	GLint link_status = GL_TRUE;
	char* log = NULL;

	glLinkProgram(shader._Program);
	
	/* verification du succes du lien */
	glGetProgramiv(shader._Program, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE)
	{
		/* erreur a la compilation recuperation du log d'erreur */

		/* on recupere la taille du message d'erreur */
		glGetProgramiv(shader._Program, GL_INFO_LOG_LENGTH, &logsize);

		/* on alloue un espace memoire dans lequel OpenGL ecrira le message */
		log = malloc(logsize + 1);
		if (log == NULL)
		{
			fprintf(stderr, "impossible d'allouer de la memoire !\n");
			return 0;
		}
		/* initialisation du contenu */
		memset(log, '\0', logsize + 1);

		glGetProgramInfoLog(shader._Program, logsize, &logsize, log);
		fprintf(stderr, "impossible de lier le programme", log);

		/* ne pas oublier de liberer la memoire  */
		free(log);

		return false;
	}
	
	return true;
}

bool DestroyProgram(GLShader* shader)
{
	glDeleteProgram(shader->_Program);
	shader->_Program = 0;
	return true;
}