
# Simple SDL mini Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g 
LDFLAGS =
LDLIBS = -lm 

SRC = metro.c graph.c

OBJ = ${SRC:.c=.o}                                                              
DEP = ${SRC:.c=.d} 

all: metro

metro: ${OBJ}

run: all
	./main

.PHONY: clean

clean:
	${RM} ${OBJ} ${DEP} metro

-include ${DEP}

# END
