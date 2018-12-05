#
# Variables:
#
CC = gcc
BIN = OCR
SRC = OCR.c
OBJ = OCR.o
 
 
#
# Error Flags:
#
ERROR_CFLAGS = -Wall -Wextra -std=c99
 
 
#
# Compiler Flags:
#
GTK_CFLAGS = $$(pkg-config --cflags gtk+-3.0)
SDL_CFLAGS = $$(pkg-config --cflags sdl -MMD)
 
CFLAGS = $(ERROR_CFLAGS) $(GTK_CFLAGS) $(SDL_CFLAGS)
 
 
#
# Link Editor Flags:
#
GTK_LDFLAGS = $$(pkg-config --libs gtk+-3.0)
GLADE_LDFLAGS = $$(pkg-config --libs gmodule-2.0)
 
LDFLAGS = $(ERROR_CFLAGS) $(GTK_LDFLAGS) $(GLADE_LDFLAGS)
 
LDLIBS = `pkg-config --libs sdl` -lSDL_image

#
# Building of the program:
#
all: $(BIN)
 
$(BIN): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(LDFLAGS) -o $(BIN) $(OBJ)
 
 
#
# Cleaning:
#
clean:
	rm -f *.o *~ core $(BIN)
