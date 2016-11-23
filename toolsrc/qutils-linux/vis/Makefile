#vis - linux makefile - jlamorie@ingenia.com

#definitions
EXE=vis
VISOBJS = ../common/cmdlib.o ../common/mathlib.o ../common/bspfile.o \
	vis.o flow.o soundpvs.o
CC=gcc
CFLAGS= -Wall -O4 -DLINUX -I../common/
LDFLAGS= -lm

#calls

vis:	$(VISOBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(VISOBJS) $(LDFLAGS)

clean:
	rm *.o $(EXE)