#pragma once
#include "InputComponent.h"
#include "StarTrekBulletManager.h"
#include "Observable.h"

class GunInputComponent :
	public InputComponent, public Observable
{
public:
	GunInputComponent(Observer* bulletsManager, SDL_Keycode shootCode, Uint8 shotsPerInterval, Uint32 timeInterval);
	~GunInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time,
		const SDL_Event& event);
protected :
	SDL_Keycode shootCode_;
	Observer* bulletsManager_;
	Uint8 shotsPerInterval_;
	Uint32 timeInterval_;

	uint32_t start_interval;

	Uint8 counter_;
};

