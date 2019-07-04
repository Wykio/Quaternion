#ifndef MATRIX4_H
#define MATRIX4_H

#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "Vec3.h"

struct Matrix4
{
	// Cette matrice suit la convention colonne d'abord (column-major) 
	// on a donc les 4 premiers float qui representent la premiere colonne, etc...
	union {
		struct {
			float col0[4];
			float col1[4];
			float col2[4];
			float col3[4];
		};
		float m[16];
	};

	Matrix4() {
		loadIdentity();
	}
	Matrix4(float m00, float m01, float m02, float m03,
			float m04, float m05, float m06, float m07,
			float m08, float m09, float m10, float m11,
			float m12, float m13, float m14, float m15) 
	{
		m[0] = m00;  m[1] = m01;  m[2] = m02;  m[3] = m03;
		m[4] = m04;  m[5] = m05;  m[6] = m06;  m[7] = m07;
		m[8] = m08;  m[9] = m09;  m[10] = m10; m[11] = m11;
		m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
	}

	void loadIdentity() {
		static const float i[] = { 1.f, 0.f, 0.f, 0.f,
									0.f, 1.f, 0.f, 0.f,
									0.f, 0.f, 1.f, 0.f,
									0.f, 0.f, 0.f, 1.f };
		load(i);
	}

	//Renvoie une matrice zero
	static Matrix4 loadZeroMatrix()
	{
		return Matrix4 (0.f, 0.f, 0.f, 0.f,
						0.f, 0.f, 0.f, 0.f,
						0.f, 0.f, 0.f, 0.f,
						0.f, 0.f, 0.f, 0.f );
	}

	// permet de charger le contenu de la matrice avec un tableau de 16 float (4 colonnes * 4 lignes)
	void load(const float* data) {
		memcpy(m, data, sizeof(float) * 16);
	}
	
	Matrix4 operator*(Matrix4 b);

	//Calcule la matrice de vue
	static Matrix4 lookAt(Vec3 eye, Vec3 center, Vec3 up);

	//Calcule la matrice de projection
	static Matrix4 perspective(float fov, float aspectRatio, float nearClipPlane, float farClipPlane);
};

#endif  // MATRIX4_H 