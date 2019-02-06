#pragma once
#include "PhysicsComponent.h"
class RotationPhysics : public PhysicsComponent
{
public:
	RotationPhysics();
	~RotationPhysics();
private:
	virtual void update(GameObject* o, Uint32 time);
};

