# Network Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =
LDLIBS = -lm

SRC = network.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: network

main: ${OBJ}

clean:
	${RM} ${OBJ}    # remove object files
	${RM} ${DEP}    # remove dependency files
	${RM} network      # remove main program

-include ${DEP}

# END
