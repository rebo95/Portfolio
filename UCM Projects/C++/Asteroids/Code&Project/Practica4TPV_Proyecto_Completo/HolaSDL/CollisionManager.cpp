#include "CollisionManager.h"



CollisionManager::CollisionManager(SDLGame* game, BulletsManager* bulletsManager, FightersManager* fighterManager, AsteroidsManager* astroidManger):GameObject(game), bulletsManager_(bulletsManager),
fighterManager_(fighterManager), asteroidsManager_(astroidManger)
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::update(Uint32 time) {
	vector<Bullet*> bullets = bulletsManager_->getBullets();
	// con esto obtenemos el array completo de los elementos que está gestionando el manager de cada tipo
	//esto es , coge el vetor correspondiente a cada 
	vector<Asteroid*> asteroids = asteroidsManager_->getAsteroids();
	Fighter* fighter = fighterManager_->getFighter();

	//la clase collisions lo que nos va a permitir va a ser estudiar esas colisiones, es una clase de apoyo
	// en este update va a ser donde comprobemos todas las colisiones, entre los respectivos elementos de los vectores de cada tipo


	//COLISIONES ASTEROIDES NAVE
	for (GameObject* o : asteroids) {
		if (Collisions::collidesWithRotation(fighter,o) && !l) {
			if (static_cast<Asteroid*>(o)->isActive() && static_cast<Fighter*>(fighter)->isActive()) {
				Message* m = new AstroidFighterCollision(static_cast<Asteroid*>(o), static_cast<Fighter*>(fighter));
				send(m);

				delete(m);
				m = nullptr;
			}
		}
	}

	//COLISIONES BALAS NAVE
	for (GameObject* b : bullets) {
		if (Collisions::collidesWithRotation(fighter, b) && !l) {
			if (static_cast<Bullet*>(b)->isActive() && static_cast<Fighter*>(fighter)->isActive()) {
				 Message* m = new BulletFighterCollision(static_cast<Bullet*>(b) , static_cast<Fighter*>(fighter));
				send(m);

				delete(m);
				m = nullptr;
			}

		}
	}
	//COLISIONES BALAS ASTEROIDES 
	for (GameObject* o1 : bullets)
		for (GameObject* o2 : asteroids) {
		if (Collisions::collidesWithRotation(o1,o2)) {
			if(static_cast<Bullet*>(o1)->isActive() && static_cast<Asteroid*>(o2)->isActive()) {
 				Message* m = new BulletAstroidCollision(static_cast<Bullet*>(o1), static_cast<Asteroid*>(o2));
				// el struct de colision que lleva este mensaje contiene los punteros a los dos objetos que colisionan
				send(m);

				delete(m);
				m = nullptr;
			}
		}
	}
}

