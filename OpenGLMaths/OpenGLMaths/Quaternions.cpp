#include "Quaternions.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Matrix4.h"


Quaternions::Quaternions(float xi, float yi, float zi, float wi)
{
    //ctor
        x = xi;
        y = yi;
        z = zi;
        w = wi;
}

Quaternions::~Quaternions()
{
	//dtor
}

Matrix4 Quaternions::MatrixVersion(Quaternions q)
{
	return Matrix4(q.x, -q.y, -q.z, -q.w, q.y, q.x, -q.w, q.z, q.z, q.w, q.x, -q.y, q.w, -q.z, q.y, q.x);
}

//TODO : matrice to quaternion

Quaternions Quaternions::GetqConj(Quaternions q)
{
    Quaternions qConj(q.x, -q.y, -q.z, -q.w);
    return qConj;
}

//calcule de la norme
float Quaternions::Norme(Quaternions q)
{
        float norme = sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
        q.norme = norme;
        return q.norme;
}

//division par sa norme
Quaternions Quaternions::Normalizeq(float norme, Quaternions q)
{
    norme = q.norme;
    q.x /= q.norme;
    q.y /= q.norme;
    q.z /= q.norme;
    q.w /= q.norme;

    return q;
}

void Quaternions::Display()
{
	std::cout << this->x << " 0 0 0" << std::endl;
	std::cout << "0 " << this->y << " 0 0" << std::endl;
	std::cout << "0 0 " << this->z << " 0" << std::endl;
	std::cout << "0 0 0 " << this->w << std::endl;
	std::cout << std::endl;
}

Quaternions Quaternions::Location(Quaternions q, Vec3 rotationAxes, float angle)
{
	q.x = cos(angle / 2);
	q.y = rotationAxes.x * sin(angle / 2);
	q.z = rotationAxes.y * sin(angle / 2);
	q.w = rotationAxes.z * sin(angle / 2);

	return q;
}


//matrice de rotation
Matrix4 Quaternions::rotationMatrix(Quaternions q)
{
    Matrix4 rotationMat = {1- 2*pow(q.y, 2) -2*pow(q.z, 2), 2*q.x * q.y-2*q.w*q.z, 2 * q.x* q.z+2*q.w*q.y, 0,
                                              2*q.x*q.y+2*q.w*q.z, 1-2*pow(q.x, 2)-2*pow(q.z, 2), 2*q.y*q.z+2*q.w*q.x, 0,
                                              2*q.x*q.z-2*q.w*q.y, 2*q.y*q.z-2*q.w*q.x, 1-2*pow(q.x, 2)-2*pow(q.y, 2), 0,
                                              0, 0, 0 ,1};
    return rotationMat;
}


//TODO : version matrice à quaternion
//TODO: translation de matrice



