#include "Light.h"

GLuint cont = 0;

Light::Light()
{

	if (cont < GL_MAX_LIGHTS) {
		id = GL_LIGHT0 + cont;
		++cont;
		glEnable(id);
	}
}


Light::~Light()
{
	disable();
}

void Light:: disable() { 
	if (id < GL_LIGHT0 + GL_MAX_LIGHTS) 
	{ 
		glDisable(id); 
	}
}


void Light::enable() {
	if (id < GL_LIGHT0 + GL_MAX_LIGHTS) 
	{
		glEnable(id); 
	}
}

void Light::load(){

	glLightfv(id, GL_AMBIENT, value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR, value_ptr(specular));

}
void Light::load(glm::dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));

	glLightfv(id, GL_AMBIENT, value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR, value_ptr(specular));
}


void Light::setAmb(glm::fvec4 amb) {
	ambient = amb;
}

void Light::setSpec(glm::fvec4 spec) {
	specular = spec;
}
void Light::setDif(glm::fvec4 dif) {
	diffuse = dif;
}

void Light::setPos(glm::fvec3 pos) {
	posDir = glm::fvec4(pos, 1.0); // método que convierte la luz en posicional 
}

void Light::setDir(glm::fvec3 dir) {
	posDir = glm::fvec4(dir, 0.0); // método que convierte la luz en en direccional 
}
