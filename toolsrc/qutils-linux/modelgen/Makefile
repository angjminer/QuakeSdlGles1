# Makefile for modelgen - for linux by jlamorie@ingenia.com 

#definitions
EXE = modelgen
MODELOBJS = ../common/cmdlib.o ../common/scriplib.o ../common/trilib.o ../common/mathlib.o ../common/lbmlib.o modelgen.o
CC=gcc
CFLAGS = -Wall -O4 -DLINUX -I../common/
LDFLAGS = -lm

#calls

modelgen: $(MODELOBJS)
	  $(CC) $(CFLAGS) $(LDFLAGS) -o $(EXE) $(MODELOBJS)

clean:
	rm *.o $(EXE)
