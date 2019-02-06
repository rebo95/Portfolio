#include "myInputComp.h"



myInputComp::myInputComp(SDL_Keycode clockWise, SDL_Keycode counterClockwise, double degrees) : wise(clockWise), counterWise(counterClockwise), rotationDegrees(degrees)
{
}


myInputComp::~myInputComp()
{
}

void myInputComp :: handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {
	Vector2D actualDirection = o->getDirection();
	if (event.type == SDL_KEYDOWN) {
		if(event.key.keysym.sym == wise){
			actualDirection.rotate(-rotationDegrees);
		}
		else if (event.key.keysym.sym == counterWise) {
			actualDirection.rotate(rotationDegrees);
		}
	}
	o->setDirection(actualDirection);
}
