OBJ = alloc.o matrice_io.o matrice_calcul.o main.o
FILES = alloc.c matrice_io.c matrice_calcul.c main.c
EXE = main
CC = gcc
CFLAGS = -Wall -Wextra
LFLAGS = -lm

all: $(EXE)

main: $(OBJ)
	$(CC) $(OBJ) -o $@ $1

%.o: %.c
	$(CC) $(FILES) -c $(CFLAGS)
