#ifndef QUATERNIONS_H
#define QUATERNIONS_H

class Quaternions
{
    public:
        Quaternions(float xi, float yi, float zi, float wi);
        virtual ~Quaternions();

        float x;
        float y;
        float z;
        float w;

        float q[];
        float qConj[];

        Quaternions operator * (Quaternions &q)
        {
          return Quaternions(
            - x*q.x - y*q.y - z*q.z + w*q.w,
           x*q.w + y*q.z - z*q.y +  w*q.x,
           y*q.w + z*q.x - x*q.z + w*q.y ,
           z*q.w + x*q.y - y*q.x + w*q.z);
        }

    protected:

    private:
//        float[] qConj(float q[]);
};

#endif // QUATERNIONS_H
