all: clean build run

CC						= gcc
CFLAGS					= $(shell python3-config --cflags)
LDFLAGS					= $(shell python3-config --ldflags) -lpython3.12
PYTHON_EXTENSION_SUFFIX = $(shell python3-config --extension-suffix)

clean:
	rm -rf build/ __pycache__/
	rm -f hello.c
	rm -f *.so

libhello.so:
	python3 setup.py build_ext --inplace
	ln -sf hello$(PYTHON_EXTENSION_SUFFIX) libhello.so

build: libhello.so
	$(CC) say_hello.c $(CFLAGS) $(LDFLAGS) -L. -lhello -o say_hello

.PHONY: all clean libhello.so build
