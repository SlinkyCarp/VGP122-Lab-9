//			{
//				switch (event.type)
//				{
//					/** Check if user tries to quit the window */
//				case SDL_QUIT:
//					done = true;		// Break out of loop to end game
//					break;
//
//					/**	Check if the ESC key was pressed */
//				case SDL_KEYDOWN:
//					
//					/**	Check if 'ESC' was pressed */
//					if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
//						done = true;	// Break out of loop to end game
//
//					/**	Check if 'SPACE' was pressed */
//					if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
//					{
//						/** Start jump cycle */
//						luigi->startJump();
//					}
//					break;
//					
//									luigi->walkRight();
//								}
//							}
//						}
//						if (event.jaxis.axis == 1)
//						{
//
//							/* Up-Down movement code goes here */
//
//							// ****** Up
//							if (event.jaxis.value < -3200)
//							{
//								std::cout << event.jaxis.value << std::endl;
//								luigi->lookUp();
//							}
//
//							// ****** Down
//							else if (event.jaxis.value > 3200)
//							{
//								std::cout << event.jaxis.value << std::endl;
//								luigi->duck();
//							}
//						}
//					}
//					break;
//				}
//			}
//
//			/** Directly read from Keyboard */
//			const Uint8 *keys = SDL_GetKeyboardState(nullptr);
//
//			/**	Check if 'LEFT' and 'RIGHT' cursor keys were pressed */
//			if (keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_RIGHT])
//			{
//				/**	Sprite should be idle (no animation, no movement) */
//				luigi->stop();
//			}
//			else if (keys[SDL_SCANCODE_LEFT] )
//			{
//				if (luigi->getXPos() <= 200)
//				{
//					luigi->setBackgroundScrolling(true);
//					background->move(10, 0); // cartesian plane, positive is right and negative is left
//				}
//				else
//				{
//					luigi->setBackgroundScrolling(false);
//				}
//
//				//stop background from moving when left edge of screen is hit by Luigi
//				if (background->getXPos() > 0)
//				{
//					luigi->setBackgroundScrolling(false);
//					background->move(-10, 0);
//				}
//
//				//Walk left only if Luigi is not at the left edge of screen
//				if (luigi->getXPos() > 0)
//				{
//					luigi->walkLeft();
//				}
//				
//			}
//			else if (keys[SDL_SCANCODE_RIGHT] )
//			{
//				
//				if (luigi->getXPos() >= 400)
//				{
//					luigi->setBackgroundScrolling(true);
//					background->move(-10, 0); // cartesian plane, positive is right and negative is left
//				}
//				else
//				{
//					luigi->setBackgroundScrolling(false);
//				}
//
//				if (background->getXPos() < (SCREEN_WIDTH - background->getWidth()))
//				{
//					luigi->setBackgroundScrolling(false);
//					background->move(10, 0);
//					
//				}
//
//				//screen size inhibitor
//				if (luigi->getXPos() < (SCREEN_WIDTH - luigi->getWidth()))
//				{
//					luigi->walkRight();
//				}			
//			}
//			/*
//			else if (SDL_HAT_LEFTUP)
//			{
//				if (luigi->getXPos() < 320)
//				{
//					luigi->lookUpLeft();
//				}
//			}
//			else if (SDL_HAT_RIGHTUP)
//			{
//				if (luigi->getXPos() > 320)
//				{
//					luigi->lookUpRight();
//				}
//			}*/
//
//			else
//				luigi->stop();
//
//			/** Check for Luigi collision with coin */
//			if (coin && CollisionDetection::isColliding(luigi, coin) && coin->isVisible())
//			{
//				coin->setVisible(false);
//
//				coinsCollected++;
//
//			}
//
//			/** Update coin and other animations */
//
//			/** Check if coin exists before drawing */
//			coin->animate(0, 3);
//			
//			luigi->updateJump();
//
//			/** Draw all sprites */
//			background->draw();
//			coinHUD->draw();
//			coin->draw();
//
//			
//			/** Check if coin exists before drawing */
//			if(coin)
//				coin->draw();
//			
//			luigi->draw();
//
//			/** Update display */
//			SDL_RenderPresent(renderer);
//
//			/** update time */
//			updatedTime = SDL_GetTicks();
//		}
//	}
//
//	/** Close access to the joystick */
//	if (SDL_JoystickGetAttached(joy))
//		SDL_JoystickClose(joy);
//
//	/** Free memory used for sprites */
//	delete background;
//	delete coinHUD;
//	coinsCollected = 0;
//	delete coin;
//	delete luigi;
//
//	/** Free SDL resources */
//	SDL_DestroyRenderer(renderer);
//#include "Definitions.h"
//#include "Luigi.h"
//
//int main(int argc, char** argv)
//{
//	/** Inialize Game Variables */
//	bool			done			= false;
//	SDL_Window		*window			= nullptr;
//	SDL_Renderer	*renderer		= nullptr;
//	SDL_Texture		*texture		= nullptr;
//
//	/** Initialize Event Variables */
//	SDL_Event		event;
//
//	/** Initialize timer variables */
//	Uint32			deltaT			= 75;			// defines delay in time for updating game loop
//	Uint32			updatedTime		= 0;			// used to determine if frame rate interval has elapsed
//
//	/** Initialize joystick handling variables */
//	SDL_Joystick	*joy = nullptr;
//
//	/** Initialize sprite variables */
//	
//	Sprite			*background		= nullptr;
//	Sprite			*coin			= nullptr;
//	Sprite			*coinHUD		= nullptr;
//	Luigi			*luigi			= nullptr;
//
//	int coinsCollected = 0;
//
//	/** Initialize SDL */
//	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK) < 0)
//	{
//		std::cerr << "Unable to init SDL: " << SDL_GetError() << std::endl;
//		return 1;
//	}
//	// Close SDL at program end
//	atexit(SDL_Quit);
//
//	/** Create Window for Project */
//	window = SDL_CreateWindow("Luigi's Revenge", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//
//	if (!window)
//	{
//		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
//		return 1;
//	}
//
//	/** Create Renderer to draw to */
//	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//	if (!renderer)
//	{
//		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
//		return 1;
//	}
//
//
//
//	/** Initialize sprite properties */
//	background	= new Sprite("Images/Mario_Level1.png", 0, 0, 7251, 480, renderer);
//	coin		= new Sprite("Images/Coin_Spritesheet.png", 420, 360, 28, 32, renderer);
//	coinHUD		= new Sprite("Images/Coin_HUD.png", 0, 0, 80, 46, renderer);
//	luigi		= new Luigi("Images/Luigi_Spritesheet.png", 320, 365, 32, 64, renderer);
//
//	/** Open access to joystick */
//	joy = SDL_JoystickOpen(0);
//
//	/** Check if joystick was opened */
//	if (joy)
//	{
//		/** Print joystick 0 information */
//		std::cout << "Opened Joystick 0" << std::endl;
//		std::cout << "Name: " << SDL_JoystickName(joy) << std::endl;
//		std::cout << "Number of Axes: " << SDL_JoystickNumAxes(joy) << std::endl;
//		std::cout << "Number of Buttons: " << SDL_JoystickNumButtons(joy) << std::endl;
//		std::cout << "Number of Hats: " << SDL_JoystickNumHats(joy) << std::endl;
//	}
//	else
//		std::cerr << "Couldn't open Joystick 0" << std::endl;
//
//	/** Keep game running until done is 'true' */
//	while (!done)
//	{
//		/** Update game loop */
//		if (SDL_GetTicks() - updatedTime >= deltaT)
//		{
//			/** Poll for Events */
//			while (SDL_PollEvent(&event))
//					/**	Check if button was pressed on joystick */
//				
//				//case SDL_JOYBUTTONDOWN:
//				//
//				//	/**	Check if jump button was pressed on joystick */
//				//	std::cout << "Press Button" << event.jbutton.button << std::endl;
//				//	if (event.jbutton.button == 1)
//				//	{
//				//		/** Start jump cycle */
//				//		luigi->startJump();
//				//	}
//				case SDL_JOYAXISMOTION:  /* Handle Joystick Motion */
//					if (event.jaxis.value < -3200 || (event.jaxis.value > 3200))
//					{
//						if (event.jaxis.axis == 0)
//						{
//							if (event.jaxis.value < -3200)
//							{
//								//std::cout << event.jaxis.value << std::endl;
//
//								// ****** Left
//								if (luigi->getXPos() <= 200)
//								{
//									luigi->setBackgroundScrolling(true);
//									background->move(10, 0); // cartesian plane, positive is right and negative is left
//								}
//								else
//								{
//									luigi->setBackgroundScrolling(false);
//								}
//
//								//stop background from moving when left edge of screen is hit by Luigi
//								if (background->getXPos() > 0)
//								{
//									luigi->setBackgroundScrolling(false);
//									background->move(-10, 0);
//								}
//
//								//Walk left only if Luigi is not at the left edge of screen
//								if (luigi->getXPos() > 0)
//								{
//									luigi->walkLeft();
//								}
//							}
//							else if (event.jaxis.value > 3200)
//							{
//								//std::cout << event.jaxis.value << std::endl;
//
//								// ****** Right
//								if (luigi->getXPos() >= 400)
//								{
//									luigi->setBackgroundScrolling(true);
//									background->move(-10, 0); // cartesian plane, positive is right and negative is left
//								}
//								else
//								{
//									luigi->setBackgroundScrolling(false);
//								}
//
//								if (background->getXPos() < (SCREEN_WIDTH - background->getWidth()))
//								{
//									luigi->setBackgroundScrolling(false);
//									background->move(10, 0);
//								}
//
//								//screen size inhibitor
//								if (luigi->getXPos() < (SCREEN_WIDTH - luigi->getWidth()))
//								{
//	SDL_DestroyWindow(window);
//
//	return 0;
//}