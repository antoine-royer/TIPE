#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/flux_plastique.h"


int main(void)
{
	srand(time(NULL));

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *carte_fond = NULL;
	
	struct modele *modele = malloc(sizeof(struct modele));
	sdl_initialisation(&window, &renderer, &carte_fond, modele);

	// Calcul des points
	compute_render(&renderer, &carte_fond, modele);
	SDL_SetWindowTitle(window, "Carte des flux de plastique");

	// Attente
	exit_loop();
	
	// Fermeture de la fenêtre et désallocation des ressources
	free(modele);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(carte_fond);

	SDL_Quit();
	
	return 0;
}
