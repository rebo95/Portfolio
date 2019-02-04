#pragma once
#include <GL/freeglut.h>
#include "Pixmap32RGBA.h"
#include <gtc/type_ptr.hpp>
#include <string>
class Textures
{
public:
	Textures() {};
	~Textures() { if (id != 0) glDeleteTextures(1, &id); };
	bool load(const std::string & BMP_Name, GLubyte alpha = 255);
	bool load(const std::string & BMP_Name, glm::ivec3 color, GLubyte alpha);
	// cargar y transferir a openGL
	void bind(GLuint mix);
	void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
	void loadColorBuffer(GLsizei width, GLsizei height);
	void save(const std::string & BMP_Name);
	void wrap(GLuint wp = GL_CLAMP);
protected:
	GLuint w, h; // dimensiones de la imagen
	GLuint id; // identificador interno (GPU) de la textura
	void init();


};


