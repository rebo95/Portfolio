#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(Texture* image, int cols, int fils, int clipX, int clipY) : image_(image), numCols_(cols), numFils_(fils), clipX_(clipX), clipY_(clipY) {
clip = new SDL_Rect();
}

ImageRenderer::~ImageRenderer() {
	delete(clip);
	clip = nullptr;
}

void ImageRenderer::render(GameObject* o, Uint32 time) {
	SDL_Rect rect
		RECT(o->getPosition().getX(), o->getPosition().getY(),
			o->getWidth(), o->getHeight());
	Vector2D v = { 0,-1 };
	 // mejor hacer estos como parámetro de entrada del propio image renderer para podel poner la nave a nuestro gusto

	clip->h = image_->getHeight()/numFils_;
	clip->w = image_->getWidth()/ numCols_;
	clip->x = clipX_*clip->w;
	clip->y = clipY_*clip->h;
	image_->render(o->getGame()->getRenderer(), rect, v.angle(o->getDirection()),clip);

}

void ImageRenderer::render(GameObject* o, Uint32 time, int x, int y, int w, int h) {

	clip->h = image_->getHeight() / numFils_;
	clip->w = image_->getWidth() / numCols_;
	clip->x = clipX_*clip->w;
	clip->y = clipY_*clip->h;

	SDL_Rect rect
		RECT(x, y,
			w, h);
	image_->render(o->getGame()->getRenderer(), rect, clip);
}