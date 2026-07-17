# Hello, C-Python World!

*This example uses simplified code from the first exercise in the course on
[Python bindings to Compiled Languages](https://github.com/Cambridge-ICCS/python-bindings-summer-school-2026)
by Mikolaj Kowalski at the
[2026 Institute of Computing for Climate Science (ICCS) summer school](https://iccs.cam.ac.uk/events/institute-computing-climate-science-annual-summer-school-2026).*

This example demonstrates how to print a message to screen from C++ in Python
using C-Python.

The [`hello.cpp`](hello.cpp) file contains everything required to set up a
Python module in C. We create a module of type `PyModuleDef` that contains a
single method called `hello`, which is of type `PyMethodDef`. The module is
initialised with the `PyInit_hello` function.

A [`CMakeLists.txt`](CMakeLists) file is provided for building the example.
Let's build in a subdirectory `build`. Running
```sh
cmake -B build
cmake --build .
```
should generate several files including a shared object file with a name of the
form `hello-cpython-<vn>-<arch>.so`, where `<vn>` indicates the Python version
(without the `.`) and `<arch>` indicates the computer architecture. If this file
is in the `PYTHONPATH` then Python programs are able to import the associated
module.

The [`say_hello.py`](say_hello.py) file contains a Python program that imports
the `hello` module defined in C and calls its `hello` method:
```python
import hello

hello.hello()
```
To run this, you will need the shared object file to be in the path. There are
several ways to do this:

1. Move or copy the shared object file from the build directory to the current
   working directory and run `say_hello.py` from here.
2. Move `say_hello.py` into the build directory and run it there.
3. Put the shared object file in the `PYTHONPATH` by updating it with something
   like `export PYTHONPATH="${PYTHONPATH}:$(pwd)/build"`.

With the shared object file in the path, run the Python script with
```sh
python3 say_hello.py
```
You should see the following printed to the console:
```
Hello from C!
```
