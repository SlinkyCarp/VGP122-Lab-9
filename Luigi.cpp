#include "Luigi.h"

Luigi::Luigi(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer)
	: Sprite(filename, xpos, ypos, width, height, renderer)
{
	this->backgroundScrolling = false;
	/** Create a new Jump action */
	this->jump = new Jump();
}

Luigi::~Luigi()
{
	/** Delete Jump action that was created */
	delete this->jump;
}

void Luigi::walkLeft()
{
	/** Call animate function with appropriate frames */
	this->animate(2, 5);

	/** Call move function with appropriate speed */
	if (!this->backgroundScrolling)
	{
		this->move(-10, 0);
	}
}

void Luigi::walkRight()
{
	/** Call animate function with appropriate frames */
	this->animate(6, 9);

	/** Call move function with appropriate speed */
	if (!this->backgroundScrolling)
	{
		this->move(10, 0);
	}
}

void Luigi::duck()
{
	if (getCurrentFrame() < 6)
	{
		setCurrentFrame(1);
	}
	else
	{
		setCurrentFrame(10);
	}
}


void Luigi::lookUp()
{
	if (getCurrentFrame() < 6)
	{
		setCurrentFrame(0);
	}
	else
	{
		setCurrentFrame(11);
	}
}

void Luigi::stop()
{
	/** Check frame Sprite is in to make Sprite face that direction */
	if (getCurrentFrame() < 6)
		/** Set frame to Idle in appropriate direction */
		setCurrentFrame(5);
	else
		/** Set frame to Idle in appropriate direction */
		setCurrentFrame(6);
}

void Luigi::startJump()
{
	/** Keep trak of Y position of Sprite */
	jump->start(getYPos());
}

void Luigi::updateJump()
{
	/** Update Y position of Sprite */
	jump->update(this);
}

bool Luigi::getBGScroll()
{
	return this->backgroundScrolling;
}

void Luigi::setBGScroll(bool scroll)
{
	this->backgroundScrolling = scroll;
}