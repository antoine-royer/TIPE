#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../include/mvt_brownien.h"

void sdl_initialisation(SDL_Window **window, SDL_Renderer **renderer)
{
	// Initialisation de la SDL
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WIN_W, WIN_H, SDL_WINDOW_SHOWN, window, renderer);

	// Initialisation du rendu
	SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
	SDL_RenderClear(*renderer);
	SDL_RenderPresent(*renderer);
	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(*window, "Mouvement brownien [CHARGEMENT EN COURS]");
}


void compute_render(SDL_Renderer *renderer)
{
	// Initialisation des coordonées du premier point
	int x = WIN_W / 2;
	int y = WIN_H / 2;
	
	for (int i = 0; i < NB_STEP; i++)
	{
		// Envoie du point courant sur le buffer
		SDL_RenderDrawPoint(renderer, x, y);
		SDL_RenderDrawPoint(renderer, x, y);

		// Calcul du point suivant
		int direction = randint(0, 2);
		if (direction <= 1)
		{
			if (DX > randint(0, 100)) x ++;
			else x --;
		}
		if (direction >= 1)
		{
			if (DY > randint(0, 100)) y --;
			else y ++;
		}
		
		if (y <= 0) y = 0;
		if (y >= WIN_H) y = WIN_H;
		if (x <= 0) x = 0;
		if (x >= WIN_W) x = WIN_W;
		
	}
	SDL_RenderPresent(renderer);
}


void exit_loop(void)
{
	int exit = 0;
	SDL_Event event;

	while (!exit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				exit = 1;
				break;
		}
	}
}


int randint(const int minimum, const int maximum)
{
	return rand() % (maximum + 1) + minimum;
}
