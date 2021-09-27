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
