#pragma once
#include "Light.h"


class SpotLight : public Light
{
private :
	GLfloat dir[3];
	//const GLfloat dir[3];
	double alpha;
public:
	SpotLight();
	~SpotLight();

	virtual void load(glm::dmat4 const& modelViewMat);
	void setFocalDirection(GLfloat x, GLfloat y, GLfloat z);
	void setAlpha(double angle);
};

