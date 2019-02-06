#include "FightersManager.h"



FightersManager::FightersManager(SDLGame* game, Observer* bulletsManger) : GameObject(game), Observer(), fighter_(Fighter(game)), rotationComp_(myInputComp(SDLK_LEFT, SDLK_RIGHT, 5)),
accelerationComp_(AccelerationImputComponent(SDLK_UP, SDLK_DOWN, 0.8, 0.8, 5)), gunComp1_(GunInputComponent(static_cast<StarTrekBulletManager*>(bulletsManger), SDLK_SPACE, 1, 500)),
gunComp2_(GunInputComponent(static_cast<StarTrekBulletManager*>(bulletsManger), SDLK_SPACE, 1, 200)), circularMotionComp_(CircularMotionPhysics()),
renderComp_(ImageRenderer(game_->getResources()->getImageTexture(Resources::SpaceShips), 8, 3, 0, 0)), renderCompBaged_(ImageRenderer(game_->getResources()->getImageTexture(Resources::SpaceShips), 8, 3, 0, 1))
{
	fighter_.setWidth(50);
	fighter_.setHeight(50);

	fighter_.setActive(false);
	fighter_.addInputComponent(&rotationComp_);
	fighter_.addInputComponent(&accelerationComp_);
	fighter_.addInputComponent(&gunComp1_);

	fighter_.addPhysicsComponent(&circularMotionComp_);

	fighter_.addRenderComponent(&renderComp_);

	badged_= false;
}


FightersManager::~FightersManager()
{
}

void FightersManager::receive(Message* msg) {
	switch (msg->id_)
	{
	case ROUND_START:
		fighter_.setActive(true);
		fighter_.setPosition(Vector2D(300, 300));
		fighter_.setDirection(Vector2D(0, -1));
		fighter_.setVelocity(Vector2D(0, 0));
		break;
	case ROUND_OVER:
		fighter_.setActive(false);
		if (badged_) {
			badged_ = false;
			fighter_.delInputComponent(&gunComp2_);
			fighter_.addInputComponent(&gunComp1_);
			fighter_.delRenderComponent(&renderCompBaged_);
			fighter_.addRenderComponent(&renderComp_);
		}
		break;
	case BADGE_ON:
		badged_ = true;
		fighter_.delRenderComponent(&renderComp_);
		fighter_.delInputComponent(&gunComp1_);
		fighter_.addInputComponent(&gunComp2_);
		//de la misma manera se tiene que indicar el badge_ON con un cambio de aspecto.
		fighter_.addRenderComponent(&renderCompBaged_);
		break;
	case BADGE_OFF:
		badged_ = false;
		fighter_.delInputComponent(&gunComp2_);
		fighter_.addInputComponent(&gunComp1_);
		fighter_.delRenderComponent(&renderCompBaged_);
		fighter_.addRenderComponent(&renderComp_);
		break;
	}
}


Fighter* FightersManager::getFighter() {
	return &fighter_;
}
void FightersManager::render(Uint32 time){
	if (fighter_.isActive())
		fighter_.render(time);

}
void FightersManager::update(Uint32 time) {
	if(fighter_.isActive())
		fighter_.update(time);

}

 void FightersManager::handleInput(Uint32 time, const SDL_Event& event) {
	 if (fighter_.isActive())
		 fighter_.handleInput(time, event);
}

