#include "Quaternions.h"
#include <stdlib.h>
#include <math.h>

Quaternions::Quaternions(float xi, float yi, float zi, float wi)
{
    //ctor
        x = xi;
        y = yi;
        z = zi;
        w = wi;

        qMat.resize(4);
        for (int i = 0; i < 4; i++)
        {
            qMat.resize(4);
        }

        qMat[0] = { x, -y, -z, -w };
        qMat[1] = { y, x, -w, z };
        qMat[2] = { z, w, x, -y };
        qMat[3] = { w, -z, y, x };
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




