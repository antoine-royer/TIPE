#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/flux_plastique.h"
#include "../include/carte_vecteurs.h"


void sdl_initialisation(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **carte_fond, struct modele *modele)
{
	// Initialisation de la SDL
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WIN_W, WIN_H, SDL_WINDOW_SHOWN, window, renderer);

	// Initialisation du rendu
	SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
	SDL_RenderClear(*renderer);
	SDL_RenderPresent(*renderer);
	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(*window, "Carte des flux de plastique [CHARGEMENT EN COURS]");

	// Initialisation de la carte
	SDL_Surface *carte_vierge = IMG_Load("ressources/carte_vierge.png");
	*carte_fond = SDL_CreateTextureFromSurface(*renderer, carte_vierge);
	
	// Initialisation du modele
	for (int y = 0; y < WIN_H; y++)
	{
		for (int x = 0; x < WIN_W; x++)
		{
			if (courants[y][x][0] != 0 && courants[y][x][1] != 0 && randint(1, 100) < PROBA_PART)
				modele->grille[y][x] = 1;
		}
	}

	// Désallocation des ressources inutiles
	SDL_FreeSurface(carte_vierge);

	printf("Temps estimé : %d minute(s)\n", (STEPS / 100) / 60);

}


void compute_render(SDL_Renderer **renderer, SDL_Texture **carte_fond, struct modele *modele)
{
	for (int i = 0; i < STEPS; i++)
	{
		display_grid(renderer, carte_fond, modele);

		for (int y = 0; y < WIN_H; y ++)
		{
			for (int x = 0; x < WIN_W; x++)
			{ 
				if (courants[y][x][0] != 0 && courants[y][x][1] != 0 && modele->grille[y][x] > 0)
				{
					int direction = randint(0, 2);
					int new_x = x, new_y = y;
					
					// Déplacement selon x
					if (direction <= 1)
					{
						if (courants[y][x][0] > randint(0, 100))
							new_x = (x + 1) % WIN_W;
						else
						{
							if (x - 1 < 0) new_x = (x + WIN_W - 1) % WIN_W;
							else new_x = (x - 1) % WIN_W;
						}
					}

					// Déplacement selon y
					if (direction >= 1)
					{
						if (courants[y][x][1] > randint(0, 100))
						{
							if (y - 1 < 0) new_y = (y + WIN_H - 1) % WIN_H;
							else new_y = (y - 1) % WIN_H;
						}
						else
							new_y = (y + 1) % WIN_H;
					}

					// Mise à jour de la grille
					if (courants[new_y][new_x][0] != 0 && courants[new_y][new_x][1] != 0)
					{
						modele->grille[y][x] --;
						modele->grille[new_y][new_x] ++;
					}
				}
				if (courants[y][x][0] == 0 || courants[y][x][1] == 0 || modele->grille[y][x] < 0)
					modele->grille[y][x] = 0;
			}
		}
	}
}


void display_grid(SDL_Renderer **renderer, SDL_Texture **carte_fond, const struct modele *modele)
{
	// Affichage de la grille
	SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
	SDL_RenderClear(*renderer);
	SDL_RenderCopy(*renderer, *carte_fond, NULL, NULL);

	SDL_SetRenderDrawColor(*renderer, 60, 60, 60, 255);
	
	for (int y = 0; y < WIN_H; y ++)
	{
		for (int x = 0; x < WIN_W; x ++)
		{
			if (courants[y][x][0] != 0 && courants[y][x][1] != 0 && modele->grille[y][x] > 0)
			{
				// int couleur = floor((modele->grille[y][x] / 100) * 255);
				// SDL_SetRenderDrawColor(*renderer, couleur, couleur, couleur, 255);

				SDL_RenderDrawPoint(*renderer, x, y);
			}
		}
	}
	SDL_RenderPresent(*renderer);
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
