CC = gcc
CFLAGS = -std=gnu99 -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings \
	-Wcast-align -Wformat -Wformat-security -Wmissing-format-attribute \
	-Wno-long-long -Winline -Werror -pedantic -pedantic-errors \
	-Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
	-Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast \
	-Wnested-externs -Wunused -Wuninitialized -fPIC

all: a.out

a.out: main.o task20.o
	$(CC) $(CFLAGS) main.o task20.o

main.o: main.c task20.h
	$(CC) $(CFLAGS) -c main.c

task20.o: task20.c task20.h
	$(CC) $(CFLAGS) -c task20.c

clean:
	rm -f *.o a.out
