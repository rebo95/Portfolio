#include "BadgeTimer.h"
#include "GameManager.h"



BadgeTimer::BadgeTimer()
{
	on_ = false;
	timeOn_ = SDL_GetTicks();
	timeInterval_ = 0;
}


BadgeTimer::~BadgeTimer()
{
}

void BadgeTimer ::update(GameObject*o, Uint32 time){
	GameManager* gm = static_cast<GameManager*>(o);
	if (on_) {
		if (timeOn_ + timeInterval_ <= time) {//timeOn es la hora a la que se activó, si sumamos el intervalo tenemos la hora de finalización, y time representa la hora a la que se llamó al update de este componente
			gm->setBadges(false);
			on_ = false;
		}
	}
}
void BadgeTimer::start(Uint32 timeInterval){
	on_ = true;
	timeOn_ = SDL_GetTicks();
	timeInterval_ = timeInterval;
}