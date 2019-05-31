#include "Quaternions.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdlib.h>


Quaternions::Quaternions(float xi, float yi, float zi, float wi)
{
    //ctor
        x = xi;
        y = yi;
        z = zi;
        w = wi;
}
float * MatrixVersion(Quaternions q)
{
    float qMat[16] =  { q.x, -q.y, -q.z, -q.w, q.y, q.x, -q.w, q.z, q.z, q.w, q.x, -q.y, q.w, -q.z, q.y, q.x};
    return qMat;
}

Quaternions::~Quaternions()
{
    //dtor
}

Quaternions GetqConj(Quaternions q)
{
    Quaternions qConj(q.x, -q.y, -q.z, -q.w);
    return qConj;
}


//calcule de la norme
float Norme(Quaternions q)
{
        float norme = sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
        q.norme = norme;
        return q.norme;
}

//division par sa norme
Quaternions Normalizeq(float norme, Quaternions q)
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

Quaternions Location (Quaternions q, float *rotationAxes, float angle)
{
    q.x = cos(angle/2);
    q.y = rotationAxes[0] * sin(angle/2);
    q.z = rotationAxes[1] * sin(angle/2);
    q.w = rotationAxes[2] * sin(angle/2);

    return q;
}

//matrice de rotation
float *rotationMatrix(Quaternions q)
{
    float rotationMat[16] = {1- 2*pow(q.y, 2) -2*pow(q.z, 2), 2*q.x * q.y-2*q.w*q.z, 2 * q.x* q.z+2*q.w*q.y, 0,
                                              2*q.x*q.y+2*q.w*q.z, 1-2*pow(q.x, 2)-2*pow(q.z, 2), 2*q.y*q.z+2*q.w*q.x, 0,
                                              2*q.x*q.z-2*q.w*q.y, 2*q.y*q.z-2*q.w*q.x, 1-2*pow(q.x, 2)-2*pow(q.y, 2), 0,
                                              0, 0, 0 ,1};
    return rotationMat;
}


//TODO : version matrice à quaternion
//TODO: translation de matrice



