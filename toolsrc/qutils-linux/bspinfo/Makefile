#Linux Makefile - bspinfo - ported by jlamorie@ingenia.com

# Definitions
EXE = bspinfo
BSPOBJS=../common/bspfile.o bspinfo.o ../common/cmdlib.o
CC=gcc
CFLAGS=-Wall -O4 -DLINUX -I../common/
LDFLAGS=-lm

# calls

bspinfo: $(BSPOBJS)
	$(CC) $(CFLAGS) -o bspinfo $(BSPOBJS)
clean:
	rm *.o $(EXE)


