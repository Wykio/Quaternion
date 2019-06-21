#ifndef OPENGL_COMMON_GLSHADER_H
#define OPENGL_COMMON_GLSHADER_H

// types standard depuis le C99
#include <stdint.h>
#include <stdbool.h>

typedef struct _GLShader
{
	// Un Programme fait le liens entre Vertex Shader et Fragment
	uint32_t _Program;
	//Un Vertex Shader est execute pour chaque sommet (vertex)
	//uint32_t _VertexShader;
	//Un Fragment Shader est execute pour chaque "pixel" 
	//lors de la rasterization/remplissage de la primitive
	//uint32_t _FragmentShader;
} GLShader;

extern bool CreateProgram(GLShader* shader);

extern bool LoadVertexShader(GLShader shader, const char* filename);
extern bool LoadFragmentShader(GLShader shader, const char* filename);

extern bool LinkProgram(GLShader shader);

extern bool DestroyProgram(GLShader* shader);

#endif // OPENGL_COMMON_GLSHADER_H
