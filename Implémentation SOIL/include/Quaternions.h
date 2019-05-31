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

    protected:

    private:
//        float[] qConj(float q[]);
};

#endif // QUATERNIONS_H
