CC=gcc
CFLAGS=-g
LDFLAGS=-lm -lSDL2main -lSDL2 -lSDL2_image

EXEC=flux_plastique
SRC=src/main.c src/flux_plastique.c src/carte_vecteurs.c
OBJ=$(SRC:.c=.o)

all: streams $(EXEC) clean

# Compilation Linux
flux_plastique: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

flux_plastique.o : include/flux_plastique.h include/carte_vecteurs.h
main.o: include/flux_plastique.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Mise à jour de la carte des courants
streams:
	bash courants.sh

# Nettoyage des sources
clean:
	rm src/*.o
