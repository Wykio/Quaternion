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

        float q[] = {x, y, z, w};
        float qMat[4][4];
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

//quaternions forme matricielle
//float** matq(float **qMat, Quaternions q)
//{
//     qMat = {
 //                           {q.x, -q.y, -q.z, -q.w},
 //                            {q.y, q.x, -q.w, q.z},
  //                           {q.z, q.w, q.x, -q.y},
   //                          {q.w, -q.z, q.y, q.x}
  //                       };
 //
   //     return (float**)qMat;
 //}

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


