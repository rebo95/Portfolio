#include "GunInputComponent.h"



GunInputComponent::GunInputComponent(Observer* bulletsManager, SDL_Keycode shootCode , Uint8 shotsPerInterval, Uint32 timeInterval): bulletsManager_(bulletsManager), shootCode_(shootCode), timeInterval_(timeInterval), shotsPerInterval_(shotsPerInterval)
{

	start_interval = SDL_GetTicks();
	dynamic_cast<Observable*>(this)->registerObserver(bulletsManager);
}


GunInputComponent::~GunInputComponent()
{
}

void GunInputComponent::handleInput(GameObject* o, Uint32 time,
	const SDL_Event& event) {

	Vector2D d = Vector2D(o->getDirection().getX(), o->getDirection().getY());
	Vector2D actualPosition = Vector2D(o->getPosition().getX(), o->getPosition().getY());
	Vector2D actualVelocity = Vector2D(o->getVelocity().getX(), o->getVelocity().getY());

	Vector2D df = d *fmaxf(actualVelocity.magnitude()*2,2.0);
	
	Vector2D p = Vector2D(actualPosition.getX() + o->getWidth()/2, actualPosition.getY() + o->getHeight() / 2) + d*(o->getHeight()/2);
	//el que va a poseer el componente es el caza, de esta manera o se refiere a ese objeto
	Vector2D shipDirection = o->getDirection();
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == shootCode_ && counter_< shotsPerInterval_) {//la idea es , si el número de balas es menor al shotsPerInterval se puede disparar
			//dememos hacer que cada shotsPerInterval se reinicialice el contador 
			// es necesario que pasemos el tiempo desde fuera, ya que solo entramos en este bucle desde fuera.
			Message* m = new FighterIsShooting(static_cast<Fighter*>(o), p, df);
			send(m);
			counter_++;

			delete(m);
			m = nullptr;

		}
	}

	if (SDL_GetTicks() - start_interval >= timeInterval_) {
		counter_ = 0;
		start_interval = SDL_GetTicks();
	}
}
