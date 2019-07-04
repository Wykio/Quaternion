#pragma once
#include <stdio.h>
#include<vector>
#include <iostream>

bool loadObj(
	const char* path,
	std::vector<float> & out_vertices,
	std::vector<float> & out_uvs,
	std::vector<float> & out_normals
)