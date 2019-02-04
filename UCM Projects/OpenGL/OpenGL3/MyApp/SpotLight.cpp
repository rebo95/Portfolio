#include "SpotLight.h"



SpotLight::SpotLight()
{

}


SpotLight::~SpotLight()
{
}

void SpotLight::load(glm::dmat4 const& modelViewMat) {
	Light::load(modelViewMat);
	glLightf(id, GL_SPOT_CUTOFF, alpha);
	glLightf(id, GL_SPOT_EXPONENT, 0.0);
	glLightfv(id, GL_SPOT_DIRECTION, dir);
}

void SpotLight::setAlpha(double angle) {
	alpha = angle;
}
void SpotLight::setFocalDirection(GLfloat x, GLfloat y, GLfloat z ) {
	dir[0] = x;
	dir[1] = y;
	dir[2] = z;
}