#ifndef QUATERNIONS_H
#define QUATERNIONS_H
#include <iostream>
#include <vector>
#include <stdio.h>

#include <stdlib.h>

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

        Quaternions operator * (Quaternions &q)
        {
          return Quaternions(
            - x*q.x - y*q.y - z*q.z + w*q.w,
           x*q.w + y*q.z - z*q.y +  w*q.x,
           y*q.w + z*q.x - x*q.z + w*q.y ,
           z*q.w + x*q.y - y*q.x + w*q.z);
        }

        void Display();
        Quaternions GetqConj(Quaternions q);

    protected:

    private:
//        float[] qConj(float q[]);
};

#endif // QUATERNIONS_H
