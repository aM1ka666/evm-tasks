CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic

all: main

main: main.o task20.o
	$(CC) $(CFLAGS) -o main main.o task20.o

main.o: main.c task20.h
	$(CC) $(CFLAGS) -c main.c

task20.o: task20.c task20.h
	$(CC) $(CFLAGS) -c task20.c

clean:
	rm -f *.o main
