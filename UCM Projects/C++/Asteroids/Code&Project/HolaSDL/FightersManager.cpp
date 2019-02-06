#include "FightersManager.h"



FightersManager::FightersManager(SDLGame* game, Observer* bulletsManger) : GameObject(game), Observer(), fighter_(Fighter(game)), rotationComp_(myInputComp(SDLK_LEFT, SDLK_RIGHT, 5)),
accelerationComp_(AccelerationImputComponent(SDLK_UP, SDLK_DOWN, 0.8, 0.8, 5)), gunComp1_(GunInputComponent(static_cast<StarTrekBulletManager*>(bulletsManger), SDLK_SPACE, 1, 500)),
gunComp2_(GunInputComponent(static_cast<StarTrekBulletManager*>(bulletsManger), SDLK_SPACE, 1, 200)), circularMotionComp_(CircularMotionPhysics()),
gunComp3_(MultiGunInputComponent(static_cast<StarTrekBulletManager*>(bulletsManger), SDLK_SPACE, 1, 500)),
renderComp_(ImageRenderer(game_->getResources()->getImageTexture(Resources::SpaceShips), 8, 3, 0, 0)), renderCompBaged_(ImageRenderer(game_->getResources()->getImageTexture(Resources::SpaceShips), 8, 3, 0, 1)),
badge_(BadgeRenderer(game->getResources()->getImageTexture(Resources::Badges), 3, 3, 0, 1, 40, 40, 50, 50)),
badgeSuperShot_(BadgeRenderer(game->getResources()->getImageTexture(Resources::Badges), 3, 3, 1, 0, 40, 40, 50, 50)),
badgeMultiShoot_(BadgeRenderer(game->getResources()->getImageTexture(Resources::Badges), 3, 3, 1, 2, 40, 40, 50, 50))
{
	fighter_.setWidth(50);
	fighter_.setHeight(50);

	fighter_.setActive(false);
	fighter_.addInputComponent(&rotationComp_);
	fighter_.addInputComponent(&accelerationComp_);//en input component no varía entre los diferentes badges 


	fighter_.addPhysicsComponent(&circularMotionComp_);
	fighter_.addRenderComponent(&renderComp_);




	BadgeRenderers_.push_back(nullptr);
	BadgeRenderers_.push_back(&badge_);
	BadgeRenderers_.push_back(&badgeSuperShot_);
	BadgeRenderers_.push_back(&badgeMultiShoot_);

	GunInputComponets_.push_back(&gunComp1_);
	GunInputComponets_.push_back(&gunComp2_);
	GunInputComponets_.push_back(&gunComp1_);//este va a seleccionarse cuandto tengamos el segundo badge activado , es decir, disparo normal, pero desde
	//el bullets manager se gestionará que las balas no se destruyan al colisionar.
	GunInputComponets_.push_back(&gunComp3_);

	//arrays de GunInputComponents y de Badgerenderers que nos permiten gestionar de manera más sencilla los badges y guninputs 
	// que añadimos y extraemos de la pila de ejecución 



	fighter_.addInputComponent(GunInputComponets_[0]);
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
		badgeActivate = 0;
		break;
	case ROUND_OVER:
		fighter_.setActive(false);
		if (badged_) {
			badged_ = false;
			fighter_.delInputComponent(GunInputComponets_[badgeActivate]);
			fighter_.addInputComponent(GunInputComponets_[0]);
			fighter_.delRenderComponent(BadgeRenderers_[badgeActivate]);
			badgeActivate = 0;
		}
		break;
	case BADGE_ON:
		//en el caso de los badges cuando se activa un badge simplemente añadimos un nuevo badge , cuando esté off lo quitamos
		badged_ = true;
		badgeActivate++;
		if (badgeActivate > 3)
			badgeActivate = 1;
		cout << badgeActivate;

		if(badgeActivate>0)
		fighter_.addRenderComponent(BadgeRenderers_[badgeActivate]);

		fighter_.delInputComponent(GunInputComponets_[0]);
		fighter_.addInputComponent(GunInputComponets_[badgeActivate]);
		break;

	case BADGE_OFF:
		badged_ = false;
		fighter_.delRenderComponent(BadgeRenderers_[badgeActivate]);
		fighter_.delInputComponent(GunInputComponets_[badgeActivate]);
		fighter_.addInputComponent(GunInputComponets_[0]);
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

