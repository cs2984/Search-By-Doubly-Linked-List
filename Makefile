# Makefile
# Problem Set 5
#

CC      = gcc
CFLAGS  = -g -std=c99 -Wall

EXE  = llist

SRCS = llist.c llist_test.c inputlib.c
HDRS = llist.h inputlib.h

$(EXE): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	rm -f *~ core $(EXE) *.o
	rm -rf *.dSYM

