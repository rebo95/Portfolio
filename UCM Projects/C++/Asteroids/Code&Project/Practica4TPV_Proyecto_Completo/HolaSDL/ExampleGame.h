#ifndef EXAMPLEGAME_H_
#define EXAMPLEGAME_H_

#include <vector>

#include "SDLGame.h"
#include "GameObject.h"
#include "Container.h"

#include "StarTrekBulletManager.h"
#include "FightersManager.h"
#include "AsteroidsManager.h"
#include "CollisionManager.h"
#include "GameManager.h"
#include "SoundManager.h"

class ExampleGame: public SDLGame {

public:
	ExampleGame();
	virtual ~ExampleGame();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();
	void handleInput(Uint32 time);
	void update(Uint32 time);
	void render(Uint32 time);

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;
	bool exit_;

	std::vector<GameObject*> actors_;

	GameObject* demoObj_;
	Container* demoComp_;

	Container* caza_;
	InputComponent* caza_input;
	InputComponent* caza_acceleration_component;
	InputComponent* caza_gun_component;
	PhysicsComponent* circular_Motion_Physics;
	RenderComponent* caza_render;

	InputComponent* inputComp_;
	PhysicsComponent* physicsComp_;
	RenderComponent* renderComp_;

	StarTrekBulletManager starTreckBulletsManager_;
	AsteroidsManager asteroidsManager_;
	FightersManager fightersManager_;
	CollisionManager collisionManager_;
	GameManager gameManager_;
	SoundManager soundManager_;
};

#endif /* EXAMPLEGAME_H_ */
