#include "Quaternions.h"

Quaternions::Quaternions(float xi, float yi, float zi, float wi)
{
    //ctor
        x = xi;
        y = yi;
        z = zi;
        w = wi;

        float q[] = {x, y, z, w};
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

Quaternion q Quaternion :: operator * (Quaternion q)
{
  return Quaternion(
    - x*q.x - y*q.y - z*q.z + w*q.w,
   x*q.w + y*q.z - z*q.y +  w*q.x,
   y*q.w + z*q.x - x*q.z + w*q.y ,
   z*q.w + x*q.y - y*q.x + w*q.z);
}




