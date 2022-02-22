# Simple SDL mini Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS =

OBJ = network.o
DEP = ${OBJ:.o=.d}

all: network

network: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} network

-include ${DEP}

# END
