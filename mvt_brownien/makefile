CC=gcc
CFLAGS=
LDFLAGS=-lSDL2main -lSDL2

EXEC=mvt_brownien
SRC=src/mvt_brownien.c src/mvt_brownien_animated.c src/main.c
OBJ=$(SRC:.c=.o)

all: $(EXEC) clean

# Compilation Linux
mvt_brownien: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: include/mvt_brownien.h include/mvt_brownien_animated.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Nettoyage des sources
clean:
	rm src/*.o