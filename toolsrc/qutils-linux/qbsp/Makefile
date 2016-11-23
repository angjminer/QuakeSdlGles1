# qbsp make file for linus -jlamorie@ingenia.com

#definitrions
EXE = qbsp
QBSPOBJS = ../common/mathlib.o ../common/cmdlib.o ../common/bspfile.o map.o \
	brush.o csg4.o merge.o nodraw.o portals.o outside.o \
	region.o solidbsp.o surfaces.o tjunc.o writebsp.o qbsp.o
CC=gcc
CFLAGS= -Wall -O4 -DLINUX -I../common/
LDFLAGS = -lm

#calls

qbsp: $(QBSPOBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(QBSPOBJS) $(LDFLAGS)

clean:
	rm *.o $(EXE)