#
##

CC	=	gcc 
CFLAGS	=  	-Wall
CFLAGS  +=      -D_GNU_SOURCE
CFLAGS  += 	-g

CIBLES	=	minishell cat cd chmod cp diff echo env export grep ls mv rm rmdir tail touch mkdir id

all: $(CIBLES)

clean: 
	$(RM) -f core *.o $(CIBLES) *~

run: clean all
		./minishell
