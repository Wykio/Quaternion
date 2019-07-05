#include "TextureLoader.h"
#include "stb_image.h"

GLuint LoadAndCreateTextureRGBA(const char *filename)
{
	GLuint texID;
	// 1. on cree l’objet OpenGL pour manipuler les textures
	glGenTextures(1, &texID);
	// 2. on indique que l’on souhaite travailler avec/editer cet objet
	glBindTexture(GL_TEXTURE_2D, texID);
	// 3. on parametre ensuite les details de la texture.
	// note: il est fortement recommande de specifier une valeur pour le
	// parametre GL_TEXTURE_MIN_FILTER autrement le Texture Object est
	// considere comme invalide
	// https://www.learnopengles.com/android-lesson-six-an-introductionto-texture-filtering/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// 4. on charge la bitmap, on la force en RGBA en memoire
	int w, h;// les dimensions de l’image bitmap
	unsigned char *data = stbi_load(filename, &w, &h, NULL, STBI_rgb_alpha);
	if (data) {
		// 5. on initialise le Texture Object avec les donnees de la bitmap
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		// 6. on libere la mémoire allouee pour la bitmap
		// (le contenu a été copie en mémoire video par glTexImage2D)
		stbi_image_free(data);
	}
	return texID;
}