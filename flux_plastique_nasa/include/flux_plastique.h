#ifndef _FLUX_PLASTIQUE_H
#define _FLUX_PLASTIQUE_H

// Paramètres de la fenêtre
#define WIN_H 530
#define WIN_W 1000


struct modele
{
	unsigned int grille[WIN_H][WIN_W];

	unsigned int proba;
	unsigned int max;

	unsigned long long int steps;

	uint8_t to_show;
};


// #define NB_PART 162906

// sdl_initialisation : initialise la SDL
void sdl_initialisation(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **carte_fond, struct modele *modele);

// compute_render : génère et calcule la grille
void compute_render(SDL_Renderer **renderer, SDL_Texture **carte_fond, struct modele *modele);

// display_grid : affiche la grille du modèle
void display_grid(SDL_Renderer **renderer, SDL_Texture **carte_fond, const struct modele *modele);

// display_load : affiche la barre de chargement
void display_load(SDL_Renderer **renderer, const int lenght);

// exit_loop : attend que la fenêtre soit fermée
void exit_loop(void);

// randint : renvoie un nombre aléatoire dans [minimum ; maximum]
int randint(const int minimum, const int maximum);

#endif /* _FLUX_PLASTIQUE_H */