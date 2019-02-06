#pragma once
#include "RenderComponent.h"
#include "ImageRenderer.h"
class BadgeRenderer:public RenderComponent
{
public:
	BadgeRenderer(Texture* image, int cols, int fils, int clipX, int clipY, int w, int h, int x, int y);
	~BadgeRenderer();
	virtual void render(GameObject* o, Uint32 time);

private:
	Texture * image_;
	ImageRenderer* im_;
	int numCols_, numFils_, clipX_, clipY_, height, width, posX, posY;
};

