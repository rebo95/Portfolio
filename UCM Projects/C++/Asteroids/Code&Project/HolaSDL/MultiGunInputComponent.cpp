#include "MultiGunInputComponent.h"



MultiGunInputComponent::MultiGunInputComponent(Observer* bulletsManager, SDL_Keycode shootCode, Uint8 shotsPerInterval, Uint32 timeInterval) :
	GunInputComponent(bulletsManager, shootCode,shotsPerInterval, timeInterval)
{
}


MultiGunInputComponent::~MultiGunInputComponent()
{
}

void MultiGunInputComponent::handleInput(GameObject* o, Uint32 time,
	const SDL_Event& event) {

	double angle = 60;

	Vector2D d = Vector2D(o->getDirection().getX(), o->getDirection().getY());
	Vector2D actualPosition = Vector2D(o->getPosition().getX(), o->getPosition().getY());
	Vector2D actualVelocity = Vector2D(o->getVelocity().getX(), o->getVelocity().getY());

	Vector2D df = d *fmaxf(actualVelocity.magnitude() * 2, 2.0);

	Vector2D p = Vector2D(actualPosition.getX() + o->getWidth() / 2, actualPosition.getY() + o->getHeight() / 2) + d*(o->getHeight() / 2);
	//el que va a poseer el componente es el caza, de esta manera o se refiere a ese objeto
	Vector2D shipDirection = o->getDirection();
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == shootCode_ && counter_< shotsPerInterval_) {//la idea es , si el número de balas es menor al shotsPerInterval se puede disparar
																				//dememos hacer que cada shotsPerInterval se reinicialice el contador 
																				// es necesario que pasemos el tiempo desde fuera, ya que solo entramos en este bucle desde fuera.
			for (int i = 0; i < 6; i++) {
				Message* m = new FighterIsShooting(static_cast<Fighter*>(o), p, df);
				send(m);
				df.rotate(angle); // lanzamos el mismo mensaje pero con los ángulos en los queremso que nazcan las balas 
				delete(m);
				m = nullptr;
			}
			counter_++;
		}
	}

	if (SDL_GetTicks() - start_interval >= timeInterval_) {
		counter_ = 0;
		start_interval = SDL_GetTicks();
	}
 }
