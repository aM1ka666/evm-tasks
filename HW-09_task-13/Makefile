CC = gcc
CFLAGS = -std=gnu99 -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings \
	-Wcast-align -Wformat -Wformat-security -Wmissing-format-attribute \
	-Wno-long-long -Winline -Werror -pedantic -pedantic-errors \
	-Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
	-Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast \
	-Wnested-externs -Wunused -Wuninitialized -fPIC

all: a.out

.PHONY: all clean

a.out: main.o task13.o
	$(CC) $(CFLAGS) main.o task13.o

main.o: main.c task13.h
	$(CC) $(CFLAGS) -c main.c

task13.o: task13.c task13.h
	$(CC) $(CFLAGS) -c task13.c

clean:
	rm -f main.o task13.o a.out
