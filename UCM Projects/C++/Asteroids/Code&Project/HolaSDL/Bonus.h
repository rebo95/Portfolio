#pragma once
#include "Container.h"
#include "CircularMotionPhysics.h"
#include "ImageRenderer.h"
#include "Observer.h"
#include "RotationPhysics.h"
#include "RandomMoveComponent.h"

class Bonus :
	public Container, public Observer
{
public:
	Bonus(SDLGame* game);
	~Bonus();
	Bonus* getBonus();
	virtual void receive(Message* msg);
private:
	RotationPhysics RotatePhysics_;
	ImageRenderer bonusImage_;
	RandomMoveComponent randomMove_;
	void init();
	void end();


};

