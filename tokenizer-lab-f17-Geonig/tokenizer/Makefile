all: shell

CFLAGS = -g -O2

shell: shell.o mytok.o

	cc -o shell shell.o shell.h
	cc -c  shell.h

clean:

	rm -f *.o shell shell.exe
