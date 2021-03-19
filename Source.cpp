/*
#include "Definitions.h"
#include "Luigi.h"
#include "Sprite.h"

int main(int argc, char** argv)
{
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	SDL_Texture* background{};

	SDL_Rect cameraRect = { 0,0,640,480 };

	Sprite* coins = nullptr;
	//Sprite* luigi = nullptr;

	if (SDL_INIT_VIDEO < 0)
	{
		std::cerr << "Initialization Error!" << SDL_GetError() << std::endl;
		return 1;
	}

	window = SDL_CreateWindow("Luigi's Revenge", 0, 0, 7251, 480, SDL_WINDOWEVENT_SHOWN);

	if (!window)
	{
		std::cerr << "Window creation Error!" << SDL_GetError() << std::endl;
		return 1;
	}

	renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(!renderer)
	{
		std::cerr << "Renderer creation Error!" << SDL_GetError() << std::endl;
		return 1;
	}

	background = IMG_LoadTexture(renderer, "Images/Mario_Level1.png");

	if (!background) 
	{
		std::cerr << "Background Texture creation Error!" << SDL_GetError() << std::endl;
		return 1;
	}

	coins = new Sprite("Images/Coin_Spritesheet.png", 420, 360, 28, 32, renderer);
	//luigi = new Luigi("Images/Luigi_Spritesheet.png", 320, 365, 32, 64, renderer);

	Luigi luigi("Images/Luigi_Spritesheet.png", 320, 365, 32, 64, renderer);

	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, background, &cameraRect, NULL);

	SDL_RenderPresent(renderer);

	SDL_Delay(4000);

	
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	delete coins;
	background = nullptr;
	renderer = nullptr;
	window = nullptr;

	SDL_Quit();

	return 0;
}*/