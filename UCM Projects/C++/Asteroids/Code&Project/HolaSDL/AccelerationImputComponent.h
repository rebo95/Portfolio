#pragma once
#include "InputComponent.h"
class AccelerationImputComponent :
	public InputComponent
{
private:
	SDL_Keycode accelerationKey, desaccelerationKey;
	double accelerationFactor;
	double desaccelerationFactor;
	double maxVel_;
public:
	AccelerationImputComponent(SDL_Keycode accelerate, SDL_Keycode desaccelerate, double thrust, double desThrust, double maxVel);
	~AccelerationImputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};
