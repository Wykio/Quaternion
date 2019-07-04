#ifndef QUATERNIONS_H
#define QUATERNIONS_H
#include <iostream>
#include <vector>
#include <stdio.h>

#include <stdlib.h>
#include "Matrix4.h"

class Quaternions
{
	public:
        float x;
        float y;
        float z;
        float w;
        float norme;

        Quaternions(float xi, float yi, float zi, float wi);
        virtual ~Quaternions();
		Matrix4 MatrixVersion(Quaternions q);
		Quaternions GetqConj(Quaternions q);
		float Norme(Quaternions q);
		Quaternions Normalizeq(float norme, Quaternions q);
		void Display();
		Quaternions Location(Quaternions q, float *rotationAxes, float angle);
       
		Quaternions operator * (Quaternions &q)
        {
          return Quaternions(
            - x*q.x - y*q.y - z*q.z + w*q.w,
           x*q.w + y*q.z - z*q.y +  w*q.x,
           y*q.w + z*q.x - x*q.z + w*q.y ,
           z*q.w + x*q.y - y*q.x + w*q.z);
        }
};

#endif // QUATERNIONS_H
