#include "Sprite.h"

Sprite::Sprite(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer)
{
	/** Set SDL_Renderer variable in Sprite class */
	this->renderer = renderer;

	/** Set SDL_Rect variable in Sprite class */
	rect.x = 0;
	rect.y = 0;
	rect.h = height;
	rect.w = width;

	/** Set position variable of Sprite class */
	this->xpos = xpos;
	this->ypos = ypos;

	/** Set visibility of Sprite class */
	visible = true;

	/** Load image to use for Sprite */
	load(filename);
}

Sprite::~Sprite()
{
	/** Delete any resources created */
	SDL_DestroyTexture(image);
}

void Sprite::load(const char* filename)
{
	/** Load picture for Sprite */
	image = IMG_LoadTexture(renderer, filename);

	/** Check if the Sprite was loaded */
	if (!image)
	{
		/** Bad stuff happened */
		std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
		exit(1);
	}
}

void Sprite::draw()
{
	/** Check if sprite should be drawn to the screen */
	if (this->visible)
	{
		/** Position sprite on Screen */
		SDL_Rect dest = { xpos, ypos, rect.w, rect.h };

		/** Draw Sprite to Screen */
		SDL_RenderCopy(renderer, image, &rect, &dest);
	}
}

void Sprite::animate(Uint16 startFrame, Uint16 endFrame)
{
	/** Store current animation frame */
	Uint16 currentFrame = getCurrentFrame();

	/** Check if animation should be looped back to start */
	if (currentFrame < startFrame || currentFrame > endFrame)
		/** Set animation frame back to start animation frame */
		currentFrame = startFrame;
	else
	{
		/** Increment frame */
		++currentFrame;

		/** Check if animation is passed last animation frame */
		if (currentFrame > endFrame)
			/** Set animation frame back to start animation frame */
			currentFrame = startFrame;
	}

	/** Set current animation frame of Sprite */
	setCurrentFrame(currentFrame);
}

void Sprite::move(int deltaX, int deltaY)
{
	/** Most Sprite along X with appropriate value */
	xpos += deltaX;

	/** Most Sprite along Y with appropriate value */
	ypos += deltaY;
}

void Sprite::setCurrentFrame(Uint16 frame)
{
	/** Check if SDL_Rect was properly initialized */
	if (!rect.w)
		/** Not properly initialized so end function */
		return;

	/** Calculate current frame of animation */
	rect.x = rect.w * frame;
}

void Sprite::setRow(Uint16 row)
{
	/** Check if SDL_Rect was properly initialized */
	if (!rect.h)
		/** Not properly initialized so end function */
		return;

	/** Calculate current frame of animation */
	rect.y = rect.h * row;
}

Uint16 Sprite::getRow()
{
	/** Check if SDL_Rect was properly initialized */
	if (!rect.h)
		/** Not properly initialized so end function */
		return 0;

	/** Calculate current frame of animation */
	return rect.y / rect.h;
}

Uint16 Sprite::getCurrentFrame()
{
	/** Check if SDL_Rect was properly initialized */
	if (!rect.w)
		/** Not properly initialized so end function */
		return 0;

	/** Calculate current frame of animation */
	return rect.x / rect.w;
}

/** Create Getters and Setters for private variables */
SDL_Texture *Sprite::getImage()
{
	return this->image;
}

int Sprite::getWidth()
{
	return this->rect.w;
}

int Sprite::getHeight()
{
	return this->rect.h;
}

int Sprite::getXPos()
{
	return this->xpos;
}

int Sprite::getYPos()
{
	return this->ypos;
}

bool Sprite::isVisible()
{
	return this->visible;
}

void Sprite::setWidth(int width)
{
	this->rect.w = width;
}

void Sprite::setHeight(int height)
{
	this->rect.h = height;
}

void Sprite::setXPos(int x)
{
	this->xpos = x;
}

void Sprite::setYPos(int y)
{
	this->ypos = y;
}

void Sprite::setVisible(bool visible)
{
	this->visible = visible;
}