CC=gcc
CFLAGS=
LDFLAGS=-lSDL2main -lSDL2

EXEC=mvt_brownien
SRC=src/mvt_brownien.c src/main.c
OBJ=$(SRC:.c=.o)

all: $(EXEC) clean

mvt_brownien: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: mvt_brownien.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm src/*.o