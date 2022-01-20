CC=gcc
CFLAGS=
LDFLAGS=-lSDL2main -lSDL2

EXEC=marche_aleatoire
SRC=src/marche_aleatoire.c src/marche_aleatoire_animee.c src/main.c
OBJ=$(SRC:.c=.o)

all: $(EXEC) clean

# Compilation Linux
marche_aleatoire: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: include/marche_aleatoire.h include/marche_aleatoire_animee.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Nettoyage des sources
clean:
	rm src/*.o