# Simple SDL mini Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS =

OBJ = build_city.o
DEP = ${OBJ:.o=.d}

all: build_city

build_city: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} build_city

-include ${DEP}

# END
