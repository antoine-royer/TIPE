#ifndef _MVT_BROWNIEN_H
#define _MVT_BROWNIEN_H

// Paramètres de la fenêtre
#define WIN_W 1500
#define WIN_H 800

// Paramètres du modèle
#define NB_STEP 10000
#define DX 50 // 0 % : gauche ; 100 % droite
#define DY 50 // 0 % : bas    ; 100 % haut


// sdl_initialisation : initialise la SDL
void sdl_initialisation(SDL_Window **window, SDL_Renderer **renderer);

// compute_render : affiche la mouvement brownien
void compute_render(SDL_Renderer *renderer);

// exit_loop : attend que la fenêtre soit fermée
void exit_loop(void);

// randint : renvoie un nombre aléatoire dans [minimum ; maximum]
int randint(const int minimum, const int maximum);

#endif /* _MVT_BROWNIEN_H */