#pragma once
#include "PhysicsComponent.h"
class RandomMoveComponent :
	public PhysicsComponent
{
public:
	RandomMoveComponent(SDLGame* g);
	~RandomMoveComponent();

private:
	SDLGame* g; 
	double time_ = 0;
	virtual void update(GameObject* o, Uint32 time);
};

