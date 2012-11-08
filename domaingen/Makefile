CC=gcc
CFLAGS=-I. -I/usr/include/libxml2
DEPS = xlibvirt.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: xlibvirt.o test.o
	gcc -Wextra -Wall -g -o test xlibvirt.o test.o -I. -lxml2

clean:
	rm -f ./*.o ./*~ ./core ./test
