#ifndef LUIGI_H
#define LUIGI_H

#include "Sprite.h"
#include "Jump.h"

class Luigi:public Sprite
{
public:
	Luigi(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer);
	~Luigi();

	void walkLeft();
	void walkRight();
	void duck();
	void lookUp();
	void stop();
	void startJump();
	void updateJump();

	bool getBGScroll();
	void setBGScroll(bool scroll);

private:
	Jump* jump;
	bool backgroundScrolling;
};

#endif //LUIGI_H
