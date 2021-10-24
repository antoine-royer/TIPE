#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/carte_courants.h"
#include "../include/carte_vecteurs.h"

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
	SDL_SetWindowTitle(*window, "Carte des courants [CHARGEMENT EN COURS]");

	// Initialisation de la carte
	SDL_Surface *carte_vierge = IMG_Load("carte_vierge.png");
	SDL_Texture *carte_fond = SDL_CreateTextureFromSurface(*renderer, carte_vierge);
	
	SDL_RenderCopy(*renderer, carte_fond, NULL, NULL);
	SDL_RenderPresent(*renderer);

	// Désallocation des ressources inutiles
	SDL_FreeSurface(carte_vierge);
	SDL_DestroyTexture(carte_fond);
}


void compute_render(struct modele *modele)
{
	// Initialisation du modèle
	for (int y = 0; y < WIN_H; y++)
	{
		for (int x = 0; x < WIN_W; x++)
		{
			if (courants[y][x][0] != 0 && courants[y][x][1] != 0 && randint(1, 100) < PROBA_PART)
				modele->grille[y][x] = 1;
		}
	}

	for (int i = 0; i < TIME; i++)
	{
		printf("Tour n°%d :\n", i);
		for (int y = 0; y < WIN_H; y ++)
		{
			for (int x = 0; x < WIN_W; x++)
			{ 
				if (modele->grille[y][x] > 0)
				{
					int direction = randint(0, 2);
					
					// Déplacement selon x
					if (direction == 0 || direction == 2)
					{
						if (courants[y][x][0] > randint(0, 100))
						{
							modele->grille[y][x] --;
							modele->grille[y][(x + 1) % WIN_W] ++;
						}
						else
						{
							modele->grille[y][x] --;
							modele->grille[y][(x - 1) % WIN_W] ++;
						}
					}

					// Déplacement selon y
					if (direction == 1 || direction == 2)
					{
						if (courants[y][x][1] > randint(0, 100))
						{
							modele->grille[y][x] --;
							modele->grille[(y - 1) % WIN_H][x] ++;
						}
						else
						{
							modele->grille[y][x] --;
							modele->grille[(y + 1) % WIN_H][x] ++;
						}
					}

					if (courants[y][x][0] == 0 || courants[y][x][1] == 0)
						modele->grille[y][x] = 0;
				}
			}
		}
		printf("... terminé\n");
	}
}


void display_grid(SDL_Renderer **renderer, const struct modele *modele)
{
	// Affichage de la grille
	printf("Calcul du rendu :\n");

	SDL_SetRenderDrawColor(*renderer, 60, 60, 60, 255);
	printf("... couleur : ok\n");
	for (int y = 0; y < WIN_H; y ++)
	{
		for (int x = 0; x < WIN_W; x ++)
		{

			// int couleur = floor(modele->grille[y][x] / NB_PART);
			// SDL_SetRenderDrawColor(*renderer, floor(couleur * 255), 60, 60, 255);

			SDL_RenderDrawPoint(*renderer, x, y);
			// SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	printf("... terminé\n");
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
