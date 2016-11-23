
#qcc - linux makefile - jlamorie@ingenia.com

#definitions
EXE=qcc
QCCOBJS= ../common/cmdlib.o qcc.o pr_comp.o pr_lex.o
CC=gcc
CFLAGS=-Wall -O4 -DLINUX -I../common/
LDFLAGS=-lm

#calls

qcc: 	$(QCCOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXE) $(QCCOBJS)

clean:
	rm *.o $(EXE)