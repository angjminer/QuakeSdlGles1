#texmake - linus makefile - jlamorie@ingenia.com

#definitions
EXE=texmake
TEXOBJS= ../common/cmdlib.o ../common/mathlib.o ../common/lbmlib.o \
	../common/trilib.o texmake.o
CC=gcc
CFLAGS= -Wall -O4 -DLINUX -I../common/
LDFLAGS= -lm

#calls

texmake: $(TEXOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXE)  $(TEXOBJS)

clean:
	rm *.o $(EXE)
