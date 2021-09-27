#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "../include/mvt_brownien.h"


int main(void)
{
	srand(time(NULL));
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	sdl_initialisation(&window, &renderer);

	// Calcul des points
	mainloop(renderer);
	SDL_SetWindowTitle(window, "Mouvement brownien");
	
	// Attente
	exit_loop();

	// Fermeture de la fenêtre
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	
	return 0;
}


/*
	// Initialisation de la SDL
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WIN_W, WIN_H, SDL_WINDOW_SHOWN, &window, &renderer);

	// Initialisation du rendu
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(window, "Mouvement brownien [CHARGEMENT EN COURS]");
*/