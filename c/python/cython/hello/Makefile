all: clean build

clean:
	rm -rf build/ __pycache__/
	rm -f *.c *.so

build:
	python3 setup.py build_ext --inplace

.PHONY: all clean build
