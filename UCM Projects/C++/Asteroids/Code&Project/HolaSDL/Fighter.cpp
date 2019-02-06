#include "Fighter.h"



Fighter::Fighter(SDLGame* game) : Container(game)
{
	active_ = false;
}


Fighter::~Fighter()
{
}

int Fighter::getId(){
	return id_;
}
