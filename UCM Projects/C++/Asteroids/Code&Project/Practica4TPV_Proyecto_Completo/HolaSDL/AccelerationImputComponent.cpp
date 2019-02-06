#include "AccelerationImputComponent.h"



AccelerationImputComponent::AccelerationImputComponent(SDL_Keycode accelerate, SDL_Keycode desaccelerate, double thrust, double desThrust, double maxVel) : accelerationKey(accelerate), desaccelerationKey(desaccelerate), accelerationFactor(thrust), desaccelerationFactor(desThrust), maxVel_(maxVel)
{
}


AccelerationImputComponent::~AccelerationImputComponent()
{
}
void AccelerationImputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == accelerationKey) {
			if (o->getVelocity().magnitude() > maxVel_) {
				Vector2D v = o->getVelocity();
				v.normalize();
				o->setVelocity(v * maxVel_ + o->getDirection()*accelerationFactor);

			}
			else
				o->setVelocity(o->getVelocity() + o->getDirection()*accelerationFactor);
		}
		else if (event.key.keysym.sym == desaccelerationKey) {
			if (o->getVelocity().magnitude() < 1)
			{
				o->setVelocity(Vector2D(0, 0));
			}
			else
				o->setVelocity(o->getVelocity()*desaccelerationFactor);
		}
	}

}
