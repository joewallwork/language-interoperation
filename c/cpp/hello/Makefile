all: clean build

CC	= gcc
CXX	= g++

clean:
	rm -f *.o
	rm -f say_hello

build:
	$(CXX) -c hello.cpp
	$(CC) -c main.c
	$(CXX) hello.o main.o -o say_hello
