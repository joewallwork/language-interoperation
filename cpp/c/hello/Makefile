all: clean build

CC	= gcc
CXX	= g++

build: hello.o hello.cpp
	$(CXX) hello.o hello.cpp -o hello

hello.o: hello.c hello.h
	$(CC) -c hello.c -o hello.o

clean:
	rm -f *.o hello

.PHONY: all build clean
