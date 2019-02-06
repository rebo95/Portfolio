#pragma once
#include "Container.h"
class Fighter : public Container
{
public:
	Fighter(SDLGame* game);
	virtual ~Fighter();
	int getId();

private:
	int id_;
	bool active_;
};