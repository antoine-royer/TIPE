#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "../include/marche_aleatoire.h"
#include "../include/marche_aleatoire_animee.h"


int main(void)
{
	srand(time(NULL));

	int animated = 1;
	printf("Marche aléatoire pondérée\n 1 - Version fixe\n 2 - Version animée\n> ");
	scanf("%d", &animated);

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	sdl_initialisation(&window, &renderer);

	// Calcul des points
	if (animated == 1) compute_render(renderer);
	else compute_render_animated(renderer);
	SDL_SetWindowTitle(window, "Marche aléatoire");
	
	// Attente
	exit_loop();

	// Fermeture de la fenêtre
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	
	return 0;
}
