#pragma once
#include "InputComponent.h"
class myInputComp :
	public InputComponent
{
private :
	SDL_Keycode wise, counterWise;
	double rotationDegrees;

public:
	myInputComp(SDL_Keycode clockWise, SDL_Keycode counterClockwise, double degrees);
	~myInputComp();
	virtual void handleInput(GameObject* o, Uint32 time,
		const SDL_Event& event);
};

