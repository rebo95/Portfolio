#pragma once
#include <gtc/type_ptr.hpp>
#include <GL/freeglut.h>
#include <glm.hpp>

using namespace glm;

class Light
{
public:
	Light();
	~Light();

protected:
	 // valor inicial cont = 0
	GLuint id = GL_MAX_LIGHTS; // GL_LIGHTi
	glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 }; // responsables del color del material
	glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 }; // responsable del color que percibimos 
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 }; // responsable de los brillos 
	glm::fvec4 posDir = { 0, 0, 1, 0 }; // w=0 -> vector
public:
	void disable();
	void enable();
	virtual void load();
	virtual void load(glm::dmat4 const& modelViewMat);

	void setAmb(glm::fvec4 amb);
	void setPos(glm::fvec3 pos);

	void setSpec(glm::fvec4 spec);
	void setDif(glm::fvec4 dif);

	void setDir(glm::fvec3 dir);

};

