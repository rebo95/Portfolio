#pragma once
#include <gtc/type_ptr.hpp>
#include <GL/freeglut.h>
#include <glm.hpp>

using namespace glm;

class Material
{
public:
	Material();
	~Material();
	virtual void load();
	void setGold();
	void setSilver();
	void setChrome();


private:
	fvec4 ambient, diffuse, specular; // coeficientes de reflexión
	GLfloat expF; // exponente especular
	GLuint face = GL_FRONT_AND_BACK; // ambos lados
	GLuint sh = GL_SMOOTH; // smooth shading

};

