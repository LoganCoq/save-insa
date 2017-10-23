OBJ = vehicule.o liste.o main.o
FILES = vehicule.c liste.c main.c
EXE = clean main
CC = gcc
CFLAGS = -Wall -Wextra
LFLAGS = -lm

all: $(EXE)

main: $(OBJ)
	$(CC) $(OBJ) -o $@ $1

%.o: %.c
	$(CC) $(FILES) -c $(CFLAGS)

clean:
	rm -f *.o
