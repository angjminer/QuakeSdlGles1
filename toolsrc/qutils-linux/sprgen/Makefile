#sprgen - linux makefile - jlamorie@ingenia.com

#definitions
EXE=sprgen
SPROBJS = ../common/cmdlib.o ../common/scriplib.o ../common/lbmlib.o \
	sprgen.o
CC=gcc
CFLAGS= -Wall -O4 -DLINUX -I../common/
LDFLAGS= -lm

sprgen: $(SPROBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXE) $(SPROBJS)

clean:
	rm *.o $(EXE)
