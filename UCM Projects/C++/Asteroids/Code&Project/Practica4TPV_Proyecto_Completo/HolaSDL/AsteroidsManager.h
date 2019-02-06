#pragma once
#include "GameObject.h"
#include "Observer.h"
#include "Observable.h"
#include "Asteroid.h"
#include "ImageRenderer.h"
#include "FillRectRenderer.h"
#include "Resources.h"
#include "CircularMotionPhysics.h"
#include "BasicMotionPhysics.h"
#include "RotationPhysics.h"
#include <vector>

class AsteroidsManager: public GameObject , public Observer, public Observable{
public:
	AsteroidsManager(SDLGame* game);
	virtual ~AsteroidsManager();
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual vector<Asteroid*>& getAsteroids();

	virtual void receive(Message* msg);

private:
	Asteroid* getAsteroid();
	void initAsteroids();

	vector <Asteroid*> astroids_;
	ImageRenderer asteroidImage_;
	CircularMotionPhysics cicularPhysics_;
	RotationPhysics rotationPhisics_;
	BasicMotionPhysics basicAsteroidPhysic;

	virtual void ereaseAsteroid(Asteroid* b);
	void stillAsteroids();

	Asteroid* a;
	int numOfAsteroids_;
};

