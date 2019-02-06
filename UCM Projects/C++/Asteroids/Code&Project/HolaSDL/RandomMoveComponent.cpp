#include "RandomMoveComponent.h"



RandomMoveComponent::RandomMoveComponent(SDLGame* g) : g(g)
{
	time_ = SDL_GetTicks();
}


RandomMoveComponent::~RandomMoveComponent()
{
}

void RandomMoveComponent::update(GameObject* o, Uint32 time) {


	if (time - time_ >3000) {
		o->setPosition(Vector2D(rand() % g->getWindowWidth(), rand() % g->getWindowHeight()));
		time_ = SDL_GetTicks();
	}
	//gira 0.8 grados cada objeto por cada vuelta del bucle
}


