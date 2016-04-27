DERNIERE_VERSION=3
CFLAGS=-Wall -Ofast -pthread
CC=gcc


all : Optimumv$(DERNIERE_VERSION).exe

Optimumv%.exe : Optimumv%.c Stockage.c
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm *.exe
