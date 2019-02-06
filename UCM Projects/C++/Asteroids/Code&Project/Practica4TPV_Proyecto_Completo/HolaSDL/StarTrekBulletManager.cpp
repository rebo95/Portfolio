#include "StarTrekBulletManager.h"
#include <iostream>



StarTrekBulletManager::StarTrekBulletManager(SDLGame* game): GameObject(game), BulletsManager(), bulletRenderer_(FillRectRenderer()), bulletPhysics_(BasicMotionPhysics())
{
}


StarTrekBulletManager::~StarTrekBulletManager()
{
	clean();
}

void StarTrekBulletManager::receive(Message* msg) {

	switch (msg->id_)
	{
	case BULLET_ASTROID_COLLISION:
		//habrá que desactivar la bala que choca 
			static_cast<BulletAstroidCollision*>(msg)->bullet_->setActive(false);
		break;
	case FIGHTER_SHOOT:
	{
		shoot(static_cast<FighterIsShooting*>(msg)->fighter_, static_cast<FighterIsShooting*>(msg)->bulletPosition_, static_cast<FighterIsShooting*>(msg)->bulletVelocity_);
	}
	break;
	case BULLET_FIGHTER_COLLISION:
		//static_cast<BulletAstroidCollision*>(msg)->bullet_->setActive(false);
		break;
	case GAME_OVER:
		desactivateBullets();
		break;
	case ROUND_START:
		desactivateBullets();
		break;
	case ROUND_OVER:
		desactivateBullets();
		break;
	}
}
void StarTrekBulletManager::shoot(Fighter* owner, Vector2D p, Vector2D v){
	//vector p y vector v se corresponden con las posiciones del owner
	Bullet* newBullet = getBullet();
	
	newBullet->setPosition(p);
	newBullet->setVelocity(v);

	newBullet->setActive(true);

	//ojo, se envía mensaje de que se ha creado bala, no de que se ha disparado , el que manda el mensaje de que se ha disparado va a ser cuando el fighter dispare,
	//precisamente pasándole los parámetros ncesatrios para que la bala salga de manera correcta .
	Message* m = new Message{ BULLET_CREATED };
	send(m);
}

Bullet* StarTrekBulletManager::getBullet() {

	Bullet* newBullet = nullptr;
	bool inactiveBulletFound = false;

	vector<Bullet*> ::iterator it = bullets_.begin();
	while (it != bullets_.end() && !inactiveBulletFound) {
		if (!(*it)->isActive()) {
			inactiveBulletFound = true;
			newBullet = (*it);

		}
		else ++it;
	}

	if (!inactiveBulletFound) {
		newBullet = new Bullet(game_);

		newBullet->setWidth(2);
		newBullet->setHeight(2);


		newBullet->addPhysicsComponent(&bulletPhysics_);
		newBullet->addRenderComponent(&bulletRenderer_);
		bullets_.push_back(newBullet);
	}
	return newBullet;

}

void StarTrekBulletManager::update(Uint32 time) {
	for (Bullet* b : bullets_) {
			if (b->isActive())
			b->update(time);
	}
	int i = 0;

	vector<Bullet*> ::iterator it = bullets_.begin(); // buscamos en el array de balas si existen balas desactivadas para no tener que generar nuevas
	while (it != bullets_.end()) {
		if (((*it)->getPosition().getX() > game_->getWindowWidth() || (*it)->getPosition().getY() > game_->getWindowHeight() || (*it)->getPosition().getX() < 0 || (*it)->getPosition().getY() < 0) && (*it)->isActive()) {
			(*it)->setActive(false);
		}
		else ++it;
	}
	//si se sale de la pantalla la desactivamos y evitamos que el iterador avance una posición a más. si no está fuera aumentamos el iterador y seuimos comprobando el 
	//resto de posiciones

}
void StarTrekBulletManager::render(Uint32 time) {
	for (Bullet* b : bullets_) 
		if(b->isActive())
			b->render(time);
}

void StarTrekBulletManager::desactivateBullets(){
	for (Bullet* b : bullets_) {
		b->setActive(false);
	}
}

void StarTrekBulletManager::clean() {
	for (Bullet* b : bullets_) {
		delete(b);
		b = nullptr;
	}
}


