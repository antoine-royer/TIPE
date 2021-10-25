#ifndef _FLUX_PLASTIQUE_H
#define _FLUX_PLASTIQUE_H

struct modele
{
	unsigned int grille[380][686];
};

// Paramètres du modèle
#define WIN_H 380
#define WIN_W 686
#define PROBA_PART 55
#define STEPS 10000

// #define NB_PART 162906

// sdl_initialisation : initialise la SDL
void sdl_initialisation(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **carte_fond, struct modele *modele);

// compute_render : génère et calcule la grille
void compute_render(SDL_Renderer **renderer, SDL_Texture **carte_fond, struct modele *modele);

// display_grid : affiche la grille du modèle
void display_grid(SDL_Renderer **renderer, SDL_Texture **carte_fond, const struct modele *modele);

// exit_loop : attend que la fenêtre soit fermée
void exit_loop(void);

// randint : renvoie un nombre aléatoire dans [minimum ; maximum]
int randint(const int minimum, const int maximum);

#endif /* _FLUX_PLASTIQUE_H */