CC = gcc
CFLAGS = -std=gnu99 -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings \
	-Wcast-align -Wformat -Wformat-security -Wmissing-format-attribute \
	-Wno-long-long -Winline -Werror -pedantic -pedantic-errors \
	-Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
	-Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast \
	-Wnested-externs -Wunused -Wuninitialized -fPIC

all: a.out

.PHONY: all clean

a.out: main.o task12.o
	$(CC) $(CFLAGS) main.o task12.o

main.o: main.c task12.h
	$(CC) $(CFLAGS) -c main.c

task12.o: task12.c task12.h
	$(CC) $(CFLAGS) -c task12.c

clean:
	rm -f *.o a.out
