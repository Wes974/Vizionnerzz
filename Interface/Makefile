#
# Variables:
#
CC = gcc
BIN = OCR
SRC = OCR.c
OBJ = OCR.o
 
 
#
# Flags d'erreurs:
#
ERROR_CFLAGS = -Wall -Wextra -std=c99
 
 
#
# Flags pour le compilateur:
#
#GLIB_CFLAGS = $$(pkg-config --cflags glib-3.0)
#PANGO_CFLAGS = $$(pkg-config --cflags pango)
GTK_CFLAGS = $$(pkg-config --cflags gtk+-3.0)
SDL_CFLAGS = $$(pkg-config --cflags sdl -MMD)
 
CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS) $(SDL_FLAGS) #$(GLIB_CFLAGS) $(PANGO_CFLAGS) 
 
 
#
# Flags pour l'editeur de liens:
#
#GLIB_LDFLAGS = $$(pkg-config --libs glib-3.0)
#PANGO_LDFLAGS = $$(pkg-config --libs pango)
GTK_LDFLAGS = $$(pkg-config --libs gtk+-3.0)
GLADE_LDFLAGS = $$(pkg-config --libs gmodule-2.0)
LDLIBS = $$(pkg-config --libs sdl -lSDL_image)
 
LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS) $(SDL_LDFLAGS) $(GLADE_LDFLAGS) #$(GLIB_LDFLAGS) $(PANGO_LDFLAGS) 
 
 
#
# Construction du programme:
#
all: $(BIN)
 
$(BIN): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(LDFLAGS) -o $(BIN) $(OBJ)
 
 
#
# Nettoyage:
#
clean:
	rm -f *.o *~ core $(BIN)
