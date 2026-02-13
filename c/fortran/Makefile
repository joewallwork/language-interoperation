all: clean build

CC	= gcc
FC	= gfortran

build:
	$(FC) -c hello.f90 -o hello_f.o
	$(CC) -c hello.c -o hello_c.o
	$(CC) hello_c.o hello_f.o -lgfortran -o hello

clean:
	rm -f *.mod *.o hello
