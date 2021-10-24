CC=gcc
CFLAGS=-g
LDFLAGS=-lm -lSDL2main -lSDL2 -lSDL2_image

EXEC=carte_courants
SRC=src/carte_courants.c src/main.c src/carte_vecteurs.c
OBJ=$(SRC:.c=.o)

all: $(EXEC) clean

# Compilation Linux
carte_courants: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

carte_courants.o : include/carte_courants.h include/carte_vecteurs.h
main.o: include/carte_courants.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Nettoyage des sources
clean:
	rm src/*.o