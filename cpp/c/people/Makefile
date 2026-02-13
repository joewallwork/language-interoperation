all: clean build

CXX	= g++
CC	= gcc
CXXFLAGS = -std=c++14 -Wall -Wextra

build: person.o main.o
	$(CXX) $(CXXFLAGS) person.o main.o -o people

person.o: person.c person.h
	$(CC) -c person.c -o person.o

main.o: main.cpp person.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm -f *.o *.mod people

.PHONY: all build clean
