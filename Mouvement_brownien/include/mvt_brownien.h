#ifndef _MVT_BROWNIEN_H
#define _MVT_BROWNIEN_H


#define WIN_W 1500
#define WIN_H 800
#define NB_PTS 10000000

void sdl_initialisation(SDL_Window **window, SDL_Renderer **renderer);

// mainloop : affiche la mouvement brownien
void mainloop(SDL_Renderer *renderer);

// exit_loop : attend que la fenêtre soit fermée
void exit_loop(void);

// randint : renvoie un nombre aléatoire entre minimum et maximum
int randint(const int minimum, const int maximum);

#endif /* _MVT_BROWNIEN_H */