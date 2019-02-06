#include "ExampleGame.h"
#include "DemoActor.h"
#include "Collisions.h"
#include "BasicKBCtrlComponent.h"
#include "BasicMotionPhysics.h"
#include "CircularMotionPhysics.h"
#include "AccelerationImputComponent.h"
#include "GunInputComponent.h"
#include "myInputComp.h"
#include "FillRectRenderer.h"
#include "ImageRenderer.h"



ExampleGame::ExampleGame() :
		SDLGame("Example Game", _WINDOW_WIDTH_, _WINDOW_HEIGHT_), starTreckBulletsManager_(StarTrekBulletManager(this)),fightersManager_(FightersManager(this, &starTreckBulletsManager_)), asteroidsManager_(AsteroidsManager(this)), bonus_(Bonus(this)),
	collisionManager_ (CollisionManager(this, &starTreckBulletsManager_, &fightersManager_, &asteroidsManager_, &bonus_)), gameManager_(GameManager(this)),
	soundManager_(SoundManager(this)){
	initGame();
	exit_ = false;
}

ExampleGame::~ExampleGame() {
	closeGame();
}

void ExampleGame::initGame() {
	// hide cursor
	SDL_ShowCursor(0);
	actors_.push_back(&starTreckBulletsManager_);/// si se hace game object precisamente es para que el bucle principal del juego lo gestione como un elemento más y haga su renderizado y update
	actors_.push_back(&fightersManager_);
	actors_.push_back(&asteroidsManager_);
	actors_.push_back(&collisionManager_);
	actors_.push_back(&gameManager_);
	actors_.push_back(&bonus_);

	// el que tiene que registrar a los observers es el collision manager, para el caso de detectar las colisiones
	collisionManager_.registerObserver(&soundManager_);//el sM debe oir mensajes del CollisionMG
	starTreckBulletsManager_.registerObserver(&soundManager_);//el sM debe oir mensajes del GM

	gameManager_.registerObserver(&soundManager_);//el sM debe oir mensajes del GM
	gameManager_.registerObserver(&asteroidsManager_);//el astroidsManager debe oir mensajes del GM
	gameManager_.registerObserver(&starTreckBulletsManager_);//el fighter debe oir mensajes del GM
	gameManager_.registerObserver(&fightersManager_);//el fighter debe oir mensajes del GM

	gameManager_.registerObserver(&bonus_);


	asteroidsManager_.registerObserver(&gameManager_);//el gameManager debe oir mensajes del astoridManager


	collisionManager_.registerObserver(&gameManager_);//el gM debe oir mensajes del CollisionMG
	collisionManager_.registerObserver(&soundManager_);//el sM debe oir mensajes del CollisionMG
	collisionManager_.registerObserver(&starTreckBulletsManager_);//el BulletsManagerDebe oir los mensajes del Collision Manager 
	collisionManager_.registerObserver(&fightersManager_); // El fighters Manager debe oir los mensajes del 
	collisionManager_.registerObserver(&asteroidsManager_);


	collisionManager_.registerObserver(&bonus_);

}

void ExampleGame::closeGame() {
	if (demoObj_ != nullptr)
		delete demoObj_;
	if (demoComp_ != nullptr)
		delete demoComp_;
	if (inputComp_ != nullptr)
		delete inputComp_;
	if (physicsComp_ != nullptr)
		delete physicsComp_;
	if (renderComp_ != nullptr)
		delete renderComp_;
}

void ExampleGame::start() {
	exit_ = false;
	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();

		handleInput(startTime);
		update(startTime);
		render(startTime);

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void ExampleGame::stop() {
	exit_ = true;
}

void ExampleGame::handleInput(Uint32 time) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				exit_ = true;
				break;
				// Pressing f to toggle fullscreen.
			case SDLK_f:
				int flags = SDL_GetWindowFlags(window_);
				if (flags & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(window_, 0);
				} else {
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
				}
				break;
			}
		}
		for (GameObject* o : actors_) {
			o->handleInput(time, event);
		}
	}
}

void ExampleGame::update(Uint32 time) {
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void ExampleGame::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x00000000));
	SDL_RenderClear(getRenderer());

	for (GameObject* o : actors_) {
		o->render(time);
	}
	SDL_RenderPresent(getRenderer());
}



