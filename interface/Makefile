# Simple SDL mini Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g `pkg-config --cflags sdl`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl` -lSDL -lSDL_image          

SRC = build_city.c toSDL.c tool/pixel_operations.c tool/tool_image.c ../metro/network.c ../metro/graph.c

OBJ = ${SRC:.c=.o}                                                              
DEP = ${SRC:.c=.d} 

all: build_city

build_city: ${OBJ}

run: all
	./main

.PHONY: clean

clean:
	${RM} ${OBJ} ${DEP} build_city

-include ${DEP}

# END
