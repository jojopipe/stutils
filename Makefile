CFLAGS=-std=c11 -Wall -Wextra -pedantic -D_XOPEN_SOURCE=700 -g
CC=gcc
RM= rm -f

.PHONY: all clean

all: stutils

stutils: main.c stutils.h
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) -f stutils

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
