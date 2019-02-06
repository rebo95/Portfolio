#pragma once
#include "PhysicsComponent.h"
class CircularMotionPhysics : public PhysicsComponent
{
public:
	CircularMotionPhysics();
	~CircularMotionPhysics();
private:
	virtual void update(GameObject* o, Uint32 time);
};

