#pragma once
#define GLEW_STATIC 1	
#include <glew.h>

#include <glfw3.h>
#include "Vec3.h"
#include "Vec2.h"
#include "GLShader.h"
#include <math.h>

#include "ObjImporter.h"


bool loadObj(const char * path, std::vector<float>& out_vertices, std::vector<float>& out_uvs, std::vector<float>& out_normals, std::vector<unsigned int>& out_indices)
{
	std::vector< unsigned int >vertexIndices, uvIndices, normalIndices;
	std::vector<Vec2> tempuvs;

	FILE * fp = fopen(path, "r");

	if (!fp)
	{
		printf("can't open file %s\n", path);
		exit(1);
	}
	else
	{
		printf("load: %s\n", path);
	}

	while (1)
	{
		char ch[128];
		int res = fscanf(fp, "%s", ch);

		if (res == EOF)
			break;


		if (strcmp(ch,"v") == 0)
		{
			Vec3 vertex;
			fscanf(fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			out_vertices.push_back(vertex.x);
			out_vertices.push_back(vertex.y);
			out_vertices.push_back(vertex.z);
		}
		else if (strcmp(ch, "vt") == 0)
		{
			Vec2 uvs;
			fscanf(fp, "%f %f\n", &uvs.x, &uvs.y);
			out_uvs.push_back(uvs.x);
			out_uvs.push_back(uvs.y);

		}
		else if (strcmp(ch, "vn") == 0)
		{
			Vec3 normal;
			fscanf(fp, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			out_normals.push_back(normal.x);
			out_normals.push_back(normal.y);
			out_normals.push_back(normal.z);
		}
		else if (strcmp(ch, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("It's not an obj file\n");
				return false;
			}
			out_indices.push_back(vertexIndex[0]-1);
			out_indices.push_back(vertexIndex[1]-1);
			out_indices.push_back(vertexIndex[2]-1);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			//normalIndices.push_back(normalIndex[0]);
			//normalIndices.push_back(normalIndex[1]);
			//normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		//unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		//unsigned int normalIndex = normalIndices[i];

		//Vec3 vertex = tempVertices[vertexIndex - 1];
		Vec2 uvs = tempuvs[uvIndex - 1];
		//Vec3 normal = tempNormals[normalIndex - 1];
	
		out_uvs.push_back(uvs.x);
		out_uvs.push_back(uvs.y);
	}

}
