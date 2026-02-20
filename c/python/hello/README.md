# Hello, Cython World!

Cython is a programming language that simplifies the process of writing C
extensions for Python. It allows you to write Python code that can be compiled
into C, which can lead to significant performance improvements. In this example,
we will see how to use Cython to create a simple extension module.

As usual, we start with a "Hello, World!" example. The Python code in `hello.py`
simply prints a greeting to the console:
```python
print("Hello, Cython World!")
```
This is pure Python, nothing fancy.

To 'Cythonize' it, we need to provide a `setup.py` script that instructs on how
to do this. The `setup.py` file included here contains:
```python
from setuptools import setup
from Cython.Build import cythonize

setup(ext_modules=cythonize("hello.py"))
```
We can run it with
```sh
python3 setup.py build_ext --inplace
```
This will print some rather cryptic output to the terminal:
```
Compiling hello.py because it changed.
[1/1] Cythonizing hello.py
running build_ext
building 'hello' extension
creating build/temp.linux-x86_64-cpython-312
mpicc -fno-strict-overflow -Wsign-compare -DNDEBUG -g -O2 -Wall -fPIC -I/home/user/language-interoperation/venv/include -I/usr/include/python3.12 -c hello.c -o build/temp.linux-x86_64-cpython-312/hello.o
creating build/lib.linux-x86_64-cpython-312
mpicc -shared -Wl,-O1 -Wl,-Bsymbolic-functions -Wl,-Bsymbolic-functions -Wl,-z,relro -g -fwrapv -O2 build/temp.linux-x86_64-cpython-312/hello.o -L/usr/lib/x86_64-linux-gnu -o build/lib.linux-x86_64-cpython-312/hello.cpython-312-x86_64-linux-gnu.so
copying build/lib.linux-x86_64-cpython-312/hello.cpython-312-x86_64-linux-gnu.so ->
```
```
```
This creates several files in the current directory, including the
auto-generated `hello.c` file, the compiled
`hello.cpython-312-x86_64-linux-gnu.so` shared library, and some build
artifacts inside the `build/` directory. Note that the shared library name
depends on several factors including computer architecture, operating system,
C compiler, and Python version, so it may look different on your machine.

We can then import the compiled module in Python. This is done in the
`say_hello.py` file:
```python
import hello
```
which should print to the console in the expected way.

But hang on, wouldn't we get the same behaviour from importing `hello.py`
directly, which can also be imported in this way? To convince yourself that the
Cythonized version is actually being used, try deleting or renaming the
`hello.py` file. You should find that running `say_hello.py` still works, which
means that the compiled version is being used.

This is great but we wanted to call Python from C, not Python. To do that, we
need to do a bit more work. First, link the shared library for convenience:
```sh
ln -s hello.cpython-312-x86_64-linux-gnu.so libhello.so
```
Then, we can make use of the `hello` module in the C code in `say_hello.c` - a
small program that embeds the Python interpreter and imports the compiled Cython
extension module `hello`:
```c
#include <Python.h>

int main()
{
    // Initialize the Python interpreter
    Py_InitializeEx(0);

    // Try importing the compiled extension module named 'hello'
    PyObject *pModule = PyImport_ImportModule("hello");

    // Handle failure cases
    if (pModule == NULL) {
        // Print the Python error (e.g., ModuleNotFoundError) to stderr
        PyErr_Print();
        // Finalize and exit with non-zero exit code to indicate failure
        Py_FinalizeEx();
        return 2;
    }

    // Release the reference to the module and exit
    Py_DECREF(pModule);

    // Finalize the Python interpreter
    Py_FinalizeEx();

    return 0;
}
```
Do this with
```
gcc say_hello.c $(python3-config --cflags --ldflags) -lpython3.12 -L. -lhello -o say_hello
```
assuming that you are using Python 3.12. (Modify the link flag as appropriate if
not.) Having done this, you should have an executable called `say_hello`. To run
it, you need to ensure that the current directory is in the Python path, so run
the executable with
```sh
PYTHONPATH=. ./say_hello
```
This should print the same greeting to the console, but this time it is the C
code that is calling the Python code in the Cython extension module!
