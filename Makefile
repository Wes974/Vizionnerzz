# Makefile

CC=gcc
CPPFLAGS=-MMD -D_XOPEN_SOURCE=500 `pkg-config --cflags sdl2 gtk+-3.0`
ERROR_CFLAiR=-Wall -Wextra -std=c99 -g
LDFLAGS=
LDLIBS=`pkg-config --libs sdl2 gtk+-3.0` -lSDL2_image -lm -export-dynamic -lm

SRC=    Main.c OCR.c wordSegmentation.c lineSegmentation.c charSegmentation.c greyscale_otsu.c for_show.c Basics.c segmentation.c

OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}


#For "make" instead of "make main"
all: OCR

-include ${DEP}

OCR: ${OBJ}

#OCR.o: Basics.h for_show.h greyscale_otsu.h segmentation.h
#greyscale_otsu.o: greyscale_otsu.h
#for_show.o: for_show.h
#Basics.o: Basics.h
#segmentation.o: segmentation.h
#wordSegmentation.o: wordSegmentation.h
#lineSegmentation.o: lineSegmentation.h
#charSegmentation.o: charSegmentation.h

clean:
	rm -f ${OBJ} ${DEP} OCR

# END
