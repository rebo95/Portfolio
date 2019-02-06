#pragma once
#include "GunInputComponent.h"
class MultiGunInputComponent :
	public GunInputComponent
{
public:
	MultiGunInputComponent(Observer* bulletsManager, SDL_Keycode shootCode, Uint8 shotsPerInterval, Uint32 timeInterval);
	~MultiGunInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time,
		const SDL_Event& event);
};

