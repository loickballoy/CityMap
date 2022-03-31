
# Simple SDL mini Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g 
LDFLAGS =
LDLIBS = -lm 

SRC = network.c graph.c

OBJ = ${SRC:.c=.o}                                                              
DEP = ${SRC:.c=.d} 

all: network

network: ${OBJ}

run: all
	./main

.PHONY: clean

clean:
	${RM} ${OBJ} ${DEP} network

-include ${DEP}

# END
