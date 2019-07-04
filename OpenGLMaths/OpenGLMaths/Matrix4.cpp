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
// right.x    right.y    right.z    0
// up.x       up.y       up.z       0
// forward.x  forward.y  forward.z  0
// 0          0          0          1
Matrix4 Matrix4::lookAt(Vec3 eye, Vec3 center, Vec3 tmp)
{
	//vecteur eye -> center
	Vec3 forward = (eye - center).normalise();
	Vec3 right = tmp.normalise() ^ forward;
	Vec3 up = forward ^ right;

	Matrix4 viewMatrix = Matrix4();
		
	viewMatrix.col0[0] = right.x;
	viewMatrix.col1[0] = right.y;
	viewMatrix.col2[0] = right.z;
	viewMatrix.col0[1] = up.x;
	viewMatrix.col1[1] = up.y;
	viewMatrix.col2[1] = up.z;
	viewMatrix.col0[2] = forward.x;
	viewMatrix.col1[2] = forward.y;
	viewMatrix.col2[2] = forward.z;
	viewMatrix.col0[3] = eye.x;
	viewMatrix.col1[3] = eye.y;
	viewMatrix.col2[3] = eye.z;

	return viewMatrix;
}

//Calcule la matrice de projection
Matrix4 Matrix4::perspective(float fov, float aspectRatio, float near, float far)
{
	float scale = tan(fov * 0.5 * 3.14 / 180) * near;
	float r = aspectRatio * scale;
	float l = -r;
	float t = scale;
	float b = -t;
	
	Matrix4 Result = loadZeroMatrix();
	Result.col0[0] = 2 * near / (r - l);
	Result.col1[0] = 0;
	Result.col2[0] = 0;
	Result.col3[0] = 0;

	Result.col0[1] = 0;
	Result.col1[1] = 2 * near / (t - b);
	Result.col2[1] = 0;
	Result.col3[1] = 0;

	Result.col0[2] = (r + l) / (r - l);
	Result.col1[2] = (t + b) / (t - b);
	Result.col2[2] = -(far + near) / (far - near);
	Result.col3[2] = -1;

	Result.col0[3] = 0;
	Result.col1[3] = 0;
	Result.col2[3] = -2 * far * near / (far - near);
	Result.col3[3] = 0;

	return Result;
}
