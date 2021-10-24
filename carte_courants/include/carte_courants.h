#ifndef _CARTE_COURANTS_H
#define _CARTE_COURANTS_H

struct modele
{
	unsigned int grille[380][686];
};

// Paramètres du modèle
#define WIN_H 380
#define WIN_W 686
#define PROBA_PART 50
#define NB_PART 162906
#define TIME 10


// sdl_initialisation : initialise la SDL
void sdl_initialisation(SDL_Window **window, SDL_Renderer **renderer);

// compute_render : génère et calcule la grille
void compute_render(struct modele *modele);

// display_grid : affiche la grille du modèle
void display_grid(SDL_Renderer **renderer, const struct modele *modele);

// exit_loop : attend que la fenêtre soit fermée
void exit_loop(void);

// randint : renvoie un nombre aléatoire dans [minimum ; maximum]
int randint(const int minimum, const int maximum);

#endif /* _CARTE_COURANTS_H */