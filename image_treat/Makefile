# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl2` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl2` -lSDL2_image

all: tests

tests: tests.o greyscale_otsu.o for_show.o Basics.o

tests.o: for_show.h greyscale_otsu.h
greyscale_otsu.o: greyscale_otsu.h
for_show.o: for_show.h
Basics.o: Basics.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} tests

# END
