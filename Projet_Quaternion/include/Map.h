#ifndef MAP_H
#define MAP_H

#include "../lib/freeglut/include/GL/gl.h"
#include "../lib/freeglut/include/GL/glu.h"

#include "../include/glut.h"
#include "../include/SOIL.h"

#include "Camera.h"

class Map
{
    public:
        Map();
        // Stockage des références aux textures
        GLuint ListeTextures[20];
        GLuint Skybox[6];
        void LoadTextures(void);
        void DrawGround(void);
        void DrawSkybox(Camera *cam);
    protected:
    private:
};

#endif // MAP_H
