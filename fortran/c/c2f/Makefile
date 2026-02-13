all: clean build

CC	= gcc
FC	= gfortran

build:
	$(CC) -c c2f.c -o c2f.o
	$(FC) c2f.o c2f.f90 -o c2f

clean:
	rm -f *.o c2f
