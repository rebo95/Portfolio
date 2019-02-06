#pragma once
#include "GameObject.h"
#include "Observable.h"
#include "BulletsManager.h"
#include "FightersManager.h"
#include "AsteroidsManager.h"
#include "Bonus.h"
#include "Collisions.h"


class CollisionManager:public GameObject, public Observable
{
public:
	CollisionManager(SDLGame* game, BulletsManager* bulletsManager, FightersManager* fighterManager, AsteroidsManager* astroidManger, Bonus* bonus);
	~CollisionManager();
	bool l = false;

	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time) {};
private:
	BulletsManager* bulletsManager_;
	FightersManager* fighterManager_;
	AsteroidsManager* asteroidsManager_;
	Bonus* bonus_;
};

