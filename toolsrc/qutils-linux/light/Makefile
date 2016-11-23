#Linux Makefile - light - ported by jlamorie@ingenia.com

# Definitions
EXE = light
LIGHTOBJS=../common/cmdlib.o ../common/mathlib.o ../common/bspfile.o threads.o entities.o light.o ltface.o trace.o
CC=gcc
CFLAGS = -Wall -O4 -DLINUX -I../common/
LDFLAGS = -lm
# calls

light: $(LIGHTOBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(LIGHTOBJS) $(LDFLAGS)

clean:
	rm *.o $(EXE)




