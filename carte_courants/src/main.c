#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/carte_courants.h"


int main(void)
{
	srand(time(NULL));

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	sdl_initialisation(&window, &renderer);

	// Création et initialisation de la grille
	struct modele modele;
	memset(&modele, 0, sizeof modele);
	
	// Calcul des points
	compute_render(&modele);
	display_grid(&renderer, &modele);
	SDL_SetWindowTitle(window, "Carte des courants");

	// Attente
	exit_loop();
	
	// Fermeture de la fenêtre et désallocation des ressources
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
	
	return 0;
}
