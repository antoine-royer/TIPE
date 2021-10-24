#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../include/mvt_brownien_animated.h"


void compute_render_animated(SDL_Renderer *renderer)
{
	// Initialisation des coordonées du premier point
	int x = WIN_W / 2;
	int y = WIN_H / 2;
	uint8_t screen[WIN_H][WIN_W] = {0};
	screen[y][x] = 1;
	
	for (int i = 0; i < NB_STEP; i++)
	{
		// Nettoyage de l'écran
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		// Affichage
		for (int disp_x = 0; disp_x < WIN_W; disp_x ++)
		{
			for (int disp_y = 0; disp_y < WIN_H; disp_y ++)
			{
				if (screen[disp_y][disp_x] == 1) SDL_RenderDrawPoint(renderer, disp_x, disp_y);
			}
		}
		SDL_RenderPresent(renderer);

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

		screen[y][x] = 1;		
	}
}