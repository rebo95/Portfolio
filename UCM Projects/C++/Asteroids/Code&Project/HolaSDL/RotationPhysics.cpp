#include "RotationPhysics.h"



RotationPhysics::RotationPhysics()
{
}


RotationPhysics::~RotationPhysics()
{
}

void RotationPhysics:: update(GameObject* o, Uint32 time){
	Vector2D objectDirection = o->getDirection();
	objectDirection.rotate(0.8);
	o->setDirection(objectDirection);
	//gira 0.8 grados cada objeto por cada vuelta del bucle
}
