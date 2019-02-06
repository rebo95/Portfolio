#pragma once
#include "GameObject.h"
#include "BulletsManager.h"
#include "BasicMotionPhysics.h"
#include "FillRectRenderer.h"

class StarTrekBulletManager: public GameObject, public BulletsManager
{
public:
	StarTrekBulletManager(SDLGame* game);
	virtual ~StarTrekBulletManager();

	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual std::vector<Bullet*>& getBullets() { return bullets_; };
	void shoot(Fighter* owner, Vector2D p, Vector2D v);

private :
	Bullet* getBullet();
	Bullet* b;

	virtual void receive(Message* msg);
	void desactivateBullets();
	void clean();
	std::vector<Bullet*>bullets_;
	FillRectRenderer bulletRenderer_;
	BasicMotionPhysics bulletPhysics_;
};

