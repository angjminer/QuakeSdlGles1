#qlumpy linux makefile - jlamorie@ingenia.com

#definitions
EXE=qlumpy
QLOBJS = qlumpy.o ../common/cmdlib.o ../common/scriplib.o \
	../common/lbmlib.o ../common/wadlib.o quakegrb.o
CC=gcc
CFLAGS= -Wall -O4 -DLINUX -I../common/
LDFLAGS= -lm

#calls

qlumpy: $(QLOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXE)  $(QLOBJS) 

clean: 
	rm *.o $(EXE)