#qfiles linux makefile -jlamorie@ingenia.com

#definitions
EXE = qfiles
QFOBJS = ../common/cmdlib.o qfiles.o
CC=gcc
CFLAGS = -Wall -O4 -DLINUX -I../common/
LDFLAGS=-lm

#calls

qfiles: $(QFOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXE) $(QFOBJS)

clean:
	rm *.o $(EXE)
