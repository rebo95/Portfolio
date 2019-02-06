#include "LiveRenderer.h"
#include "GameManager.h"


LiveRenderer::LiveRenderer(Texture* image, int cols, int fils, int clipX, int clipY, int w, int h, int x, int y) : image_(image), numCols_(cols), numFils_(fils), clipX_(clipX), clipY_(clipY), height(h), width(w), posX(x), posY(y)
{
	im_ = new ImageRenderer(image, cols, fils, clipX, clipY);
}


LiveRenderer::~LiveRenderer()
{
	delete(im_);
	im_ = nullptr;
}

void LiveRenderer::render(GameObject* o, Uint32 time) {

	GameManager* gm = static_cast<GameManager*>(o);// en este caso o es el game manager
	SDLGame* game = gm->getGame();

	for (int i = 0; i < gm->getLives(); i++) {
		im_->render(o,time, game->getWindowWidth() - 3 * width + width * i, posY, width, height);
	}

	// draw score
	Texture lifes(o->getGame()->getRenderer(),
		std::to_string(gm->getLives()),
		*(game->getResources()->getFont(Resources::ARIAL24)),
		{ COLOR(0xffffffff) });
	lifes.render(game->getRenderer(),
		game->getWindowWidth() - 4 * width, 10);

	Texture round(o->getGame()->getRenderer(),
		"Round : " + std::to_string(gm->getRound()),
		*(game->getResources()->getFont(Resources::ARIAL24)),
		{ COLOR(0xffffffff) });
	round.render(game->getRenderer(),
		50, 10);
}
