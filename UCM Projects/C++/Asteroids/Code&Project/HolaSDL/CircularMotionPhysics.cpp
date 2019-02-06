#include "CircularMotionPhysics.h"



CircularMotionPhysics::CircularMotionPhysics()
{
}


CircularMotionPhysics ::~CircularMotionPhysics()
{
}
void CircularMotionPhysics::update(GameObject* o, Uint32 time) {
	o->setPosition(o->getPosition() + o->getVelocity());
	
		// ahora hacemos el donut

	if (o->getPosition().getX() > o->getGame()->getWindowWidth()) {
		o->setPosition(Vector2D(0, o->getPosition().getY()));
	}
	else if (o->getPosition().getX() < 0) {
		o->setPosition(Vector2D(o->getGame()->getWindowWidth(), o->getPosition().getY()));
	}

	if (o->getPosition().getY() > o->getGame()->getWindowHeight()) {
		o->setPosition(Vector2D(o->getPosition().getX(), 0));
	}
	else if (o->getPosition().getY() < 0) {
		o->setPosition(Vector2D(o->getPosition().getX(), o->getGame()->getWindowHeight()));
	}
}