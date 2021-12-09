#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/flux_plastique.h"
#include "../include/carte_vecteurs.h"


void sdl_initialisation(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **carte_fond, struct modele *modele)
{
	// Initialisation du modele
	printf("...probabilité d'apparition des particules : ");
	scanf("%d", &modele->proba);
	printf("...nombre maximal de particule par case : ");
	scanf("%d", &modele->max);
	printf("...nombre pas de la simulation : ");
	scanf("%d", &modele->steps);
	printf("...animation [0/1] : ");
	scanf("%d", &modele->to_show);

	for (int y = 0; y < WIN_H; y++)
	{
		for (int x = 0; x < WIN_W; x++)
		{
			modele->grille[y][x] = 0;
			if (courants[y][x][0] != 0 && courants[y][x][1] != 0 && randint(1, 100) < modele->proba)
				modele->grille[y][x] = 1;
		}
	}

	// Initialisation de la SDL
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WIN_W, WIN_H, SDL_WINDOW_SHOWN, window, renderer);

	// Initialisation du rendu
	SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
	SDL_RenderClear(*renderer);
	SDL_RenderPresent(*renderer);
	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(*window, "Carte des concentrations en plastique [CHARGEMENT EN COURS]");

	// Initialisation de la carte
	SDL_Surface *carte_vierge = IMG_Load("assets/carte_vierge.png");
	*carte_fond = SDL_CreateTextureFromSurface(*renderer, carte_vierge);

	// Désallocation des ressources inutiles
	SDL_FreeSurface(carte_vierge);

	printf("...temps estimé : %d' %d''\n", (modele->steps / 100) / 60, (modele->steps / 100) % 60);

}


void compute_render(SDL_Renderer **renderer, SDL_Texture **carte_fond, struct modele *modele)
{

	if (modele->to_show % 2 == 0)
	{
		// Nettoyage de l'écran
		SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
		SDL_RenderClear(*renderer);
		SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);

		SDL_RenderDrawPoint(*renderer, 86, 188);	
		SDL_RenderDrawPoint(*renderer, 86, 189);
		SDL_RenderDrawPoint(*renderer, 86, 190);

		SDL_RenderDrawPoint(*renderer, 600, 188);	
		SDL_RenderDrawPoint(*renderer, 600, 189);
		SDL_RenderDrawPoint(*renderer, 600, 190);
	}

	for (int i = 0; i < modele->steps; i++)
	{
		if (modele->to_show % 2)
			display_grid(renderer, carte_fond, modele);
		else
			display_load(renderer, floor((i * 514) / modele->steps));

		for (int y = 0; y < WIN_H; y ++)
		{
			for (int x = 0; x < WIN_W; x++)
			{ 
				if (courants[y][x][0] != 0 && courants[y][x][1] != 0 && modele->grille[y][x] > 0)
				{
					int direction = randint(0, 3);
					int new_x = x, new_y = y;
					
					// Déplacement selon x
					if (direction == 0 || direction == 1)
					{
						if (courants[y][x][0] + 2 > randint(0, 100))
							new_x = (x + 1) % WIN_W;
						else
						{
							if (x - 1 < 0) new_x = (x + WIN_W - 1) % WIN_W;
							else new_x = (x - 1) % WIN_W;
						}
					}

					// Déplacement selon y
					if (direction == 1 || direction == 2)
					{
						if (courants[y][x][1] - 2 > randint(0, 100))
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
						int nb = 0;
						if (modele->grille[new_y][new_x] + modele->grille[y][x] <= modele->max)
							nb = modele->grille[y][x];
						
						modele->grille[new_y][new_x] += nb;
						modele->grille[y][x] -= nb;
					}
				}
			}
		}
	}
	display_grid(renderer, carte_fond, modele);
}


void display_grid(SDL_Renderer **renderer, SDL_Texture **carte_fond, const struct modele *modele)
{
	// Nettoyage de l'écran
	SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
	SDL_RenderClear(*renderer);
	
	// Affichage du fond
	SDL_RenderCopy(*renderer, *carte_fond, NULL, NULL);

	SDL_SetRenderDrawColor(*renderer, 60, 60, 60, 255);
	
	for (int y = 0; y < WIN_H; y ++)
	{
		for (int x = 0; x < WIN_W; x ++)
		{
			if (courants[y][x][0] != 0 && courants[y][x][1] != 0 && modele->grille[y][x] > 0)
			{
				
				int couleur = floor(modele->grille[y][x] * 255 / modele->max);
				SDL_SetRenderDrawColor(*renderer, couleur, 50, 255 - couleur, 255);

				SDL_RenderDrawPoint(*renderer, x, y);
			}
		}
	}
	SDL_RenderPresent(*renderer);
}


void display_load(SDL_Renderer **renderer, const int length)
{
	for (int x = 86; x <= length + 86; x ++)
	{
		SDL_RenderDrawPoint(*renderer, x, 189);
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
	return minimum + (rand() % (maximum + 1));
}
