#pragma once
#include <stdio.h>
#include<vector>
#include <iostream>
#ifndef OBJLOADER_H
#define OBJLOADER_H


bool loadObj(
	const char* path,
	std::vector<float> & out_vertices,
	std::vector<float> & out_uvs,
	std::vector<float> & out_normals,
	std::vector<float> & out_indices
);

#endif