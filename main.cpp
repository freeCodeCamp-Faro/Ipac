#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>

#include "Headers/Constants.h"
#include "Classes/Player.h"

int main(void)
{
	// Initialize.
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Could not initialize SDL: %s", SDL_GetError());
		return 1;
	}

	SDL_Window *mainWindow = nullptr;
	if((mainWindow = SDL_CreateWindow("PackMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)) == nullptr)
	{
		SDL_Log("Could not create the main window: %s", SDL_GetError());
		return 2;
	}

	SDL_Renderer *mainRenderer = nullptr;
	if((mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == nullptr)
	{
		SDL_Log("Could not create the renderer: %s", SDL_GetError());
		return 3;
	}

	// Player
	Vector2D initPosition = { 100, 100 };
	Player player(3, initPosition);

	Vector2D playerDir = { 0, 0 };

	// Delta time.
	std::uint32_t ticksCount = SDL_GetTicks();
	float deltaTime = 0;

	// Game loop.
	bool isRunning = true;

	while(isRunning)
	{
		// Limit the frame rate and get delta time.
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16))
			;

		deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
		if (deltaTime > 0.05f || deltaTime < 0.05f)
		{
			deltaTime = 0.05f;
		}
		ticksCount = SDL_GetTicks();

		SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
		SDL_RenderClear(mainRenderer);

		// Handle events.
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					isRunning = false;
					break;
				default:
					break;
			}
		}

		// Handle keyboard input.
		const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

		if(keyboardState[SDL_SCANCODE_ESCAPE])
		{
			isRunning = false;
		}

		if(keyboardState[SDL_SCANCODE_S])
		{
			playerDir.x = 0;
			playerDir.y = 1;
		}

		if(keyboardState[SDL_SCANCODE_W])
		{
			playerDir.x = 0;
			playerDir.y = -1;
		}

		if(keyboardState[SDL_SCANCODE_A])
		{
			playerDir.x = -1;
			playerDir.y = 0;
		}

		if(keyboardState[SDL_SCANCODE_D])
		{
			playerDir.x = 1;
			playerDir.y = 0;
		}

		player.UpdateDirection(playerDir);
		player.UpdatePosition(deltaTime);

		// Draw the map.
		SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, 255);

		SDL_Rect topWall = { 0, 0, WINDOW_WIDTH, BLOCK_SIZE };
		SDL_RenderFillRect(mainRenderer, &topWall);

		SDL_Rect bottomWall = { 0, WINDOW_HEIGHT - BLOCK_SIZE, WINDOW_WIDTH, BLOCK_SIZE };
		SDL_RenderFillRect(mainRenderer, &bottomWall);

		SDL_Rect botLeftWall = { 0, WINDOW_HEIGHT - ((WINDOW_HEIGHT / 2)), BLOCK_SIZE, BLOCK_SIZE * 15 };
		SDL_RenderFillRect(mainRenderer, &botLeftWall);

		SDL_Rect topLeftWall = { 0, 0, BLOCK_SIZE, BLOCK_SIZE * 15 };
		SDL_RenderFillRect(mainRenderer, &topLeftWall);

		SDL_Rect botRightWall = { WINDOW_WIDTH - BLOCK_SIZE, WINDOW_HEIGHT - ((WINDOW_HEIGHT / 2)), BLOCK_SIZE, BLOCK_SIZE * 15 };
		SDL_RenderFillRect(mainRenderer, &botRightWall);

		SDL_Rect topRightWall = { WINDOW_WIDTH - BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE * 15 };
		SDL_RenderFillRect(mainRenderer, &topRightWall);

		// Draw the player.
		SDL_SetRenderDrawColor(mainRenderer, 255, 255, 0, 255);
		SDL_Rect playerRect = { player.GetPosX(), player.GetPosY(), BLOCK_SIZE, BLOCK_SIZE };
		SDL_RenderFillRect(mainRenderer, &playerRect);

		SDL_RenderPresent(mainRenderer);
	}

	// Cleanup.
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();

	return 0;
}