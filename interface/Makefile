# Simple SDL mini Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g `pkg-config --cflags sdl` `pkg-config gtk+-3.0 --cflags`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl` -lSDL -lSDL_image `pkg-config gtk+-3.0 --libs`         

SRC = build_city.c toSDL.c tool/pixel_operations.c tool/tool_image.c ../metro/network.c ../metro/graph.c input_gtk.c

OBJ = ${SRC:.c=.o}                                                              
DEP = ${SRC:.c=.d} 

all: input_gtk

input_gtk: ${OBJ}

run: all
	./main

.PHONY: clean

clean:
	${RM} ${OBJ} ${DEP} input_gtk

-include ${DEP}

# END
