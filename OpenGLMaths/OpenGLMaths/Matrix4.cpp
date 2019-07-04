#include "Matrix4.h"
#include <math.h>

//Multiplication de matrice
Matrix4 Matrix4::operator*(Matrix4 b)
{
	Matrix4 result = loadZeroMatrix();

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			for (size_t k = 0; k < 4; ++k) {
				result.m[i + 4 * j] += m[i + 4 * k] * b.m[k + 4 * j];
			}
		}
	}

	return result;
}

//Calcule la matrice de vue
Matrix4 Matrix4::lookAt(Vec3 eye, Vec3 center, Vec3 up)
{
	//vecteur eye -> center
	Vec3 zAxis = (eye - center).normalised();
	Vec3 xAxis = (up ^ zAxis).normalised();
	Vec3 yAxis = zAxis ^ xAxis;

	Matrix4 orientation = Matrix4(
		xAxis.x, xAxis.y, xAxis.z, -xAxis.dot(eye),
		yAxis.x, yAxis.y, yAxis.z, -yAxis.dot(eye),
		zAxis.x, zAxis.y, zAxis.z, -zAxis.dot(eye),
		0, 0, 0, 1

	);

	return orientation;
}

//Calcule la matrice de projection
Matrix4 Matrix4::perspective(float fov, float aspectRatio, float nearClipPlane, float farClipPlane)
{
	float t = tan((fov * 3.14 / 180) * 0.5) * nearClipPlane; //top
	float b = -t; //bottom
	float r = aspectRatio * t; //right
	float l = -r; //left

	Matrix4 Result = loadZeroMatrix();
	Result.col0[0] = (2 ) / (r - l); ;
	Result.col1[1] = (2 ) / (t - b);
	Result.col2[2] = -2 / (farClipPlane - nearClipPlane);
	Result.col3[0] = -(r + l) / (r - l);
	Result.col3[1] = -(t + b) / (t - b);
	Result.col3[2] = -(farClipPlane + nearClipPlane) / (farClipPlane - nearClipPlane);
	Result.col3[3] = 1;

	return Result;
}
