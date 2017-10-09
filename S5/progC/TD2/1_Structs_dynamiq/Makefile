OBJ = vehicule.o main.o
FILES = vehicule.c main.c
EXE = main
CC = gcc
CFLAGS = -Wall -Wextra
LFLAGS = -lm

all: $(EXE)

main: $(OBJ)
	$(CC) $(OBJ) -o $@ $1
	
%.o: %.c
	$(CC) $(FILES) -c $(CFLAGS)

