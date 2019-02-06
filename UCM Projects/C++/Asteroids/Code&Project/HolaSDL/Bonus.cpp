#include "Bonus.h"



Bonus::Bonus(SDLGame* game) : Container(game), RotatePhysics_(RotationPhysics()), bonusImage_(ImageRenderer(game->getResources()->getImageTexture(Resources::Star), 1, 1, 0, 0)), randomMove_(RandomMoveComponent(game))
{
	this->setWidth(50);
	this->setHeight(50);
	this->addPhysicsComponent(&RotatePhysics_);
	this->addPhysicsComponent(&randomMove_);
}



Bonus::~Bonus()
{
}


void Bonus:: receive(Message* msg) {
	switch (msg->id_)
	{
	case BULLET_BONUS_COLLISION:
		this->setActive(false);
		this->delRenderComponent(&bonusImage_);
		break;
	case ROUND_START:
		init();
		break;

	case ROUND_OVER:
		end();
		break;
	}
}

Bonus* Bonus::getBonus() {
	return this;
}

void Bonus:: init() {

	this->setPosition(Vector2D(rand() % game_->getWindowWidth(), rand() % game_->getWindowHeight()));
	this->setActive(true);
	this->addRenderComponent(&bonusImage_);
}
void Bonus:: end() {

	this->setActive(false);
	this->delRenderComponent(&bonusImage_);
}