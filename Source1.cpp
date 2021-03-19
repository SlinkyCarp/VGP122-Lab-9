#include "Definitions.h"
#include "Luigi.h"

int main(int argc, char** argv)
{
	/** Inialize Game Variables */
	bool			done = false;
	bool menu = true;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;

	/** Initialize Event Variables */
	SDL_Event		event{};

	/** Initialize timer variables */
	Uint32				deltaT = 75;			// defines delay in time for updating game loop
	Uint32				updatedTime = 0;			// used to determine if frame rate interval has elapsed

	/** Initialize joystick handling variables */
	SDL_Joystick* joy = NULL;

	/** Score tracking variables */
	int				numCoins = 0;

	/** Initialize true type font variables.
		For text to be drawn, define
		- color of text
		- destination rect of location text will be drawn
		- font used
		- text surface to draw from
	*/

	// height and width are dependant on whats being rendered




/** Initialize sprite variables */
	Sprite* background = NULL;
	Sprite* coin = NULL;
	Sprite* coinHUD = NULL;
	Luigi* luigi = NULL;

	/** Initialize music and sound effect variables */




	/** Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK) < 0)
	{
		cerr << "Unable to init SDL: " << SDL_GetError() << endl;
		return 1;
	}
	/** Close SDL at program end */
	atexit(SDL_Quit);

	/** Create Window for Project */
	window = SDL_CreateWindow("Luigi's Revenge", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window)
	{
		cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		return 1;
	}

	/** Create Renderer to draw to */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
		return 1;
	}


	//Create texture for project
	texture = IMG_LoadTexture(renderer, "Images/Mario_Title.png");
	if (!texture)
	{
		{
			cerr << "Load Texture Error: " << SDL_GetError() << endl;
			return 1;
		}
	}
	/** Initialize TTF_Font */

	{


	}
	/** Close TTF_Font at program end */


	/** Initialize SDL_Mixer */

	{


	}
	/** Close SDL_Mixer at program end */


	/** Initialize sprite properties */
	background = new Sprite("Images/Mario_Level1.png", 0, 0, 7251, 480, renderer);
	coin = new Sprite("Images/Coin_Spritesheet.png", 420, 360, 28, 32, renderer);
	coinHUD = new Sprite("Images/Coin_HUD.png", 0, 0, 80, 46, renderer);
	luigi = new Luigi("Images/Luigi_Spritesheet.png", 320, 365, 32, 64, renderer);

	/** Open access to joystick */
	joy = SDL_JoystickOpen(0);

	/** Check if joystick was opened */
	if (joy)
	{
		/** Print joystick 0 information */
		cout << "Opened Joystick 0" << endl;
		cout << "Name: " << SDL_JoystickName(joy) << endl;
		cout << "Number of Axes: " << SDL_JoystickNumAxes(joy) << endl;
		cout << "Number of Buttons: " << SDL_JoystickNumButtons(joy) << endl;
		cout << "Number of Hats: " << SDL_JoystickNumHats(joy) << endl;
	}
	else
		cerr << "Couldn't open Joystick 0" << endl;

	/** Open a font to use when rendering text */


	{


	}

	/** Set style for text, if needed */


	/** Set message for text */



	/** Update width and height of destination to fit text */



	/** Load music sound file */


	/** Check if audio file was opened */



	/** Load sfx sound file */


	/** Check if audio file was opened */



	/** Load sfx sound file */


	/** Check if audio file was opened */



	/** Begin music */


	/** Keep game running until done is 'true' */
	while (!done)
	{
		
			/** Update game loop */
			if (SDL_GetTicks() - updatedTime >= deltaT)
			{
				/** Poll for Events */
				while (SDL_PollEvent(&event))
				{
					
					switch (event.type)
					{
						/** Check if user tries to quit the window */
					case SDL_QUIT:
						done = true;		// Break out of loop to end game
						break;

						/**	Check if a key was pressed */
					case SDL_KEYDOWN:

						/**	Check if 'ESC' was pressed */
						if (event.key.keysym.sym == SDLK_ESCAPE)
							done = true;	// Break out of loop to end game

						/**	Check if 'SPACE' was pressed */
						if (event.key.keysym.sym == SDLK_SPACE)
						{
							/** Start jump cycle */
							luigi->startJump();

							/** Play Jump Sound */

						}
						break;

						/**	Check if button was pressed on joystick */
					case SDL_JOYBUTTONDOWN:

						/**	Check if jump button was pressed on joystick */
						if (event.jbutton.button == 1)
						{
							/** Start jump cycle */
							luigi->startJump();

							/** Play Jump Sound */

						}
						break;
					}
				}
				while (menu == true)
				{
					while (SDL_PollEvent(&event))
					{
						SDL_RenderCopy(renderer, texture, NULL, NULL);
						SDL_RenderPresent(renderer);
						if (event.jbutton.button == 6)
						{
							SDL_DestroyTexture(texture);
							menu = false;
						}
					}
				}
				
				/** Directly read from Keyboard */
				const Uint8* keys = SDL_GetKeyboardState(NULL);

				/**	Check if 'LEFT' and 'RIGHT' cursor keys were pressed */
				if (keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_RIGHT])
				{
					/**	Sprite should be idle (no animation, no movement) */
					luigi->stop();
				}
				else if ((keys[SDL_SCANCODE_LEFT]) || (SDL_JoystickGetAxis(joy, 0) < -2500))
				{
					/** Start scrolling background to right */
					if (luigi->getXPos() <= 100)
					{
						luigi->setBGScroll(true);
						background->move(10, 0);
					}
					else
						luigi->setBGScroll(false);

					/** stop scrolling background when left boundary of background is reached */
					if (background->getXPos() > 0)
					{
						luigi->setBGScroll(false);
						background->move(-10, 0);
						coin->move(-10, 0);
					}

					/** If luigi has reached far left of screen, do not walk */
					if (luigi->getXPos() > 0)
						luigi->walkLeft();
				}
				else if ((keys[SDL_SCANCODE_RIGHT]) || (SDL_JoystickGetAxis(joy, 0) > 2500))
				{
					/** Start scrolling background to left */
					if (luigi->getXPos() >= 500)
					{
						luigi->setBGScroll(true);
						background->move(-10, 0);
					}
					else
						luigi->setBGScroll(false);

					if (background->getXPos() < (SCREEN_WIDTH - background->getWidth()))
					{
						luigi->setBGScroll(false);
						background->move(10, 0);
						coin->move(10, 0);
					}

					if (luigi->getXPos() < (SCREEN_WIDTH - luigi->getWidth()))
						luigi->walkRight();
				}
				else if ((keys[SDL_SCANCODE_UP]) || (SDL_JoystickGetAxis(joy, 1) < -8000))
				{
					luigi->lookUp();
				}
				else if ((keys[SDL_SCANCODE_DOWN]) || (SDL_JoystickGetAxis(joy, 1) > 8000))
				{
					luigi->duck();
				}
				else
				{
					luigi->stop();
				}

				/** Check for Luigi collision with coin */
				if (CollisionDetection::isColliding(coin, luigi) && coin->isVisible())
				{
					/** Print message to console */
					cout << "Luigi picked a coin up\n";

					/** Play coin sound */


					/** Make coin invisible */
					coin->setVisible(false);

					/** Update score by 1 */
					numCoins++;

					/** Set message for text */



					/** Update width and height of destination to fit text */


				}

				/** Update coin and other animations */
				coin->animate(0, 3);
				luigi->updateJump();

				/** Draw all sprites */
				background->draw();
				coinHUD->draw();
				coin->draw();
				luigi->draw();

				/** Draw text to renderer*/


				/** Update display */
				SDL_RenderPresent(renderer);

				/** update time */
				updatedTime = SDL_GetTicks();
			}

	}

	/** Close access to the joystick */
	if (SDL_JoystickGetAttached(joy))
		SDL_JoystickClose(joy);


	//** Free up memory
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	/** Free memory used for sprites */
	delete background;
	delete coinHUD;
	delete coin;
	delete luigi;

	//** Nullify
	texture = nullptr;
	renderer = nullptr;
	window = nullptr;
	
	/** Stop and free music. Free all sound effects */





	/** Free text surfaces */




	return 0;
}