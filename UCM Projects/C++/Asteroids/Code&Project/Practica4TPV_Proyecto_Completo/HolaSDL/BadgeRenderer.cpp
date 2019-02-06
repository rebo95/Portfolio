#include "BadgeRenderer.h"
#include "GameManager.h"


BadgeRenderer::BadgeRenderer(Texture* image, int cols, int fils, int clipX, int clipY, int w, int h, int x, int y): image_(image), numCols_(cols), numFils_(fils), clipX_(clipX), clipY_(clipY), height(h), width(w), posX(x), posY(y)
{
	im_ = new ImageRenderer(image, cols, fils, clipX, clipY);
}


BadgeRenderer::~BadgeRenderer()
{
	delete(im_);
	im_ = nullptr;
}


void BadgeRenderer::render(GameObject* o, Uint32 time) {
	GameManager* gm = static_cast<GameManager*>(o);// en este caso o es el game manager
	SDLGame* game = gm->getGame();
	if (gm->isBadged())
	im_->render(o, time, posX, posY, width, height);
	// mejor hacer estos como parámetro de entrada del propio image renderer para podel poner la nave a nuestro gusto
}

