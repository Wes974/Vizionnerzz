# Network Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3 -D_POSIX_C_SOURCE=199309L
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
