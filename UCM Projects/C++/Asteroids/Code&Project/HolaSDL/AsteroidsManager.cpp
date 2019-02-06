#include "AsteroidsManager.h"



AsteroidsManager::AsteroidsManager(SDLGame* game) : GameObject(game), Observer(),Observable(), asteroidImage_ (ImageRenderer(game_->getResources()->getImageTexture(Resources::Astroid), 1, 1, 0, 0)),
cicularPhysics_(CircularMotionPhysics()), rotationPhisics_ (RotationPhysics()), basicAsteroidPhysic(BasicMotionPhysics())
{
	//initAsteroids();
}


AsteroidsManager::~AsteroidsManager()
{
	for (Asteroid* a : astroids_) {
		delete(a);
		a = nullptr;
	}
}

void AsteroidsManager::receive(Message* msg){
	switch (msg->id_)
	{
	case BULLET_ASTROID_COLLISION:

		a = static_cast<BulletAstroidCollision*>(msg)->astroid_;
			if (a->getGenerations() > 0)
				for (int i = 0; i < 1; i++)
					getAsteroid();
			a->setActive(false); 
			numOfAsteroids_--;
			stillAsteroids();
		break;
	case ASTROID_FIGHTER_COLLISION:
		if (static_cast<BulletAstroidCollision*>(msg)->astroid_->isActive()) {
		}
		break;
	case ROUND_START:
		numOfAsteroids_ = 0;
		initAsteroids();
		break;
	}
}

void AsteroidsManager::initAsteroids() {

	for (Asteroid* a : astroids_) {
		a->setActive(false);
	}

	for (int i = 0; i < 5; i++) {
		Asteroid* newAsteroid = new Asteroid(game_);

		newAsteroid->setGenerations(2);
		newAsteroid->addRenderComponent(&asteroidImage_);


		int r = rand() % 2 + 1;
		if (r == 0) {
			newAsteroid->setPosition(Vector2D( game_->getWindowWidth(), rand() % game_->getWindowHeight()));
		}
		else 
			newAsteroid->setPosition(Vector2D( 0, rand() % game_->getWindowHeight()));

		Vector2D v = Vector2D((rand() % 201 +  (-100)), (rand() % 201 + (-100)));
		newAsteroid->setVelocity(v/v.magnitude()/ 2);
		newAsteroid->setVelocity(Vector2D(0.0,0.0));

		newAsteroid->setWidth(50);
		newAsteroid->setHeight(50);

		newAsteroid->addPhysicsComponent(&cicularPhysics_);
		newAsteroid->addPhysicsComponent(&rotationPhisics_);
		newAsteroid->addPhysicsComponent(&basicAsteroidPhysic);

		newAsteroid->setActive(true);
		astroids_.push_back(newAsteroid);
		numOfAsteroids_++;

	}
}

void AsteroidsManager::update(Uint32 time) {
	for (Asteroid* a : astroids_) {
		if(a->isActive())
			a->update(time);
	}
}
void AsteroidsManager::render(Uint32 time) {
	for (Asteroid* a : astroids_) {
		if (a->isActive())
			a->render(time);
	}
}


Asteroid* AsteroidsManager::getAsteroid() {

	bool inactivAsteroidFound = false;

	Asteroid* newAsteroid = nullptr;

	//si hay alguno desactivado , cogemos ese, si no hay desaactivados , creamos nuevos, ahorramos crear recursos si ya existen 
	vector<Asteroid*> ::iterator it = astroids_.begin();
	while (it != astroids_.end()&& !inactivAsteroidFound) {
		if (!(*it)->isActive()) {
			inactivAsteroidFound = true;
			newAsteroid = (*it);

		}
		else ++it;
	}

	if (!inactivAsteroidFound) {
		newAsteroid = new Asteroid(game_);
		newAsteroid->addRenderComponent(&asteroidImage_);
		newAsteroid->addPhysicsComponent(&cicularPhysics_);
		newAsteroid->addPhysicsComponent(&rotationPhisics_);
		newAsteroid->addPhysicsComponent(&basicAsteroidPhysic);
		astroids_.push_back(newAsteroid);
	}

	Vector2D v = v = Vector2D((rand() % 201 + (-100)), (rand() % 201 + (-100)));
	while (v.getX() == a->getVelocity().getX() && v.getY() == a->getVelocity().getY()) {
		v = Vector2D((rand() % 201 + (-100)), (rand() % 201 + (-100)));
	}

	newAsteroid->setGenerations(a->getGenerations() - 1);
	newAsteroid->setPosition(Vector2D(a->getPosition()));
	newAsteroid->setVelocity(v / v.magnitude() / 2);

	newAsteroid->setVelocity(Vector2D(0.0, 0.0));
	newAsteroid->setWidth(a->getWidth()-15);
	newAsteroid->setHeight(a->getHeight() - 15);


	newAsteroid->setActive(true);
	numOfAsteroids_++;
	return newAsteroid;
}

vector<Asteroid*>& AsteroidsManager:: getAsteroids() {
	return astroids_;
}

void AsteroidsManager::ereaseAsteroid(Asteroid* a) {
	vector<Asteroid*> ::iterator it = astroids_.begin();
	while (it != astroids_.end()) {
		if ((*it) == a) {
			delete (*it);
			it = astroids_.erase(it);
		}
		else ++it;
	}
}

void AsteroidsManager::stillAsteroids() {

	if (numOfAsteroids_ == 0) {
		Message* m = new Message{ NO_MORE_ATROIDS };
		send(m);

		delete(m);
		m = nullptr;
	}
}