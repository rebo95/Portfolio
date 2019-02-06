#pragma once
#include "GameObject.h"
#include "Observer.h"
#include "CircularMotionPhysics.h"
#include "AccelerationImputComponent.h"
#include "ImageRenderer.h"
#include "myInputComp.h"
#include "GunInputComponent.h"
#include "RotationPhysics.h"

class FightersManager: public GameObject, public Observer
{
public:
	FightersManager(SDLGame* game, Observer* bulletsManager);
	~FightersManager();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	Fighter* getFighter();
	virtual void receive(Message* msg);


private:
	Fighter fighter_;
	CircularMotionPhysics circularMotionComp_;
	AccelerationImputComponent accelerationComp_;
	ImageRenderer renderComp_;
	ImageRenderer renderCompBaged_;
	myInputComp rotationComp_; //rotationInputComponent
	GunInputComponent gunComp1_;
	GunInputComponent gunComp2_;


	bool badged_;
};

