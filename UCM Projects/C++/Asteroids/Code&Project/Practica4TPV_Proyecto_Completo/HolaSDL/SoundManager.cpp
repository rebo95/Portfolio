#include "SoundManager.h"



SoundManager::SoundManager(SDLGame* game) :Observer(), game_(game)
{
}


SoundManager::~SoundManager()
{
}
void SoundManager::receive(Message* msg) {

	switch (msg->id_)
	{
	case BULLET_ASTROID_COLLISION:
		game_->getResources()->getSoundEffect(Resources::ExplosionSound)->play(0);
		break;
	case ASTROID_FIGHTER_COLLISION:
				game_->getResources()->getSoundEffect(Resources::ExplosionSound)->play(0);
		break;
	case BULLET_CREATED:
		game_->getResources()->getSoundEffect(Resources::GunShot)->play(0);
		break;
	case ROUND_START:
		game_->getResources()->getMusic(Resources::ImperialMarch)->play(0);
		break;
	case ROUND_OVER:
		game_->getResources()->getSoundEffect(Resources::GunShot)->play(0);
		game_->getResources()->getSoundEffect(Resources::ExplosionSound)->play(0);
		break; 
	}

}
