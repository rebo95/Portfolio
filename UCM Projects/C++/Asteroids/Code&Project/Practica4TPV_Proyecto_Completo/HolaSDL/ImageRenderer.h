#ifndef IMAGERENDERER_H_
#define IMAGERENDERER_H_

#include "RenderComponent.h"

/*
 *
 */
class ImageRenderer: public RenderComponent {
public:
	ImageRenderer(Texture* image, int cols, int fils, int clipX, int clipY);
	virtual ~ImageRenderer();
	virtual void render(GameObject* o, Uint32 time);
	virtual void render(GameObject* o, Uint32 time, int x, int y, int w, int h);

private:
	Texture* image_;
	SDL_Rect* clip;
	int numCols_, numFils_, clipX_, clipY_;
	int w,h, x,y;
};

#endif /* IMAGERENDERER_H_ */
