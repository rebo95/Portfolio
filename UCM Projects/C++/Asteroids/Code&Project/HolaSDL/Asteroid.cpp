#include "Asteroid.h"



Asteroid::Asteroid(SDLGame* game) : Container(game)
{
	active_ = true;
}


Asteroid::~Asteroid()
{
}

void Asteroid::setGenerations(int generation) {
	generations_ = generation;
}
int Asteroid::getGenerations() {
	return generations_;
}
