#ifndef MATRIX4_H
#define MATRIX4_H

#include <stdlib.h>
#include <string.h>
#include <memory.h>


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
	Matrix4(const float* data) {
		memcpy(m, data, sizeof(float) * 16);
	}

	void loadIdentity() {
		static const float i[] = { 1.f, 0.f, 0.f, 0.f,
									0.f, 1.f, 0.f, 0.f,
									0.f, 0.f, 1.f, 0.f,
									0.f, 0.f, 0.f, 1.f };
		load(i);
	}

	Matrix4 loadZeroMatrix()
	{
		static const float i[] = {	0.f, 0.f, 0.f, 0.f,
									0.f, 0.f, 0.f, 0.f,
									0.f, 0.f, 0.f, 0.f,
									0.f, 0.f, 0.f, 0.f };
		return Matrix4(i);
	}

	// permet de charger le contenu de la matrice avec un tableau de 16 float (4 colonnes * 4 lignes)
	void load(const float* data) {
		memcpy(m, data, sizeof(float) * 16);
	}

	// coder ici les autres fonctions 
	// (translate, scale, rotate, perspective,
	// etc...)
	
	Matrix4 operator*(Matrix4 b)
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
};

#endif  // MATRIX4_H 