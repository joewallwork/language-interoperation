# Hello, World!

Let's start with a C++ function that says hello, as defined in `hello.cpp`:
```cpp
#include "hello.h"
#include <iostream>

void say_hello() {
  std::cout << "Hello, World!" << std::endl;
}
```
Note that this file contains C++ syntax that is not contained in C. The file
includes the header file `hello.h`, which simply contains the function
declaration
```c
extern "C" void say_hello();
```
The `extern "C"` here prevents C++ name mangling, which ensures that the
function is compatible with C code.

The C++ code can be compiled with the GNU C++ compiler `g++` with
```sh
g++ -c hello.cpp
```
This produces an object file `hello.o`.

To then call the function in C, we have the `main.c` file,
```c
#include "hello.h"

int main() {
  say_hello();
  return 0;
}
```
This can be compiled with the GNU C compiler `gcc` with
```sh
gcc -c main.c
```
Then link the object files together with
```sh
g++ hello.o main.c -o say_hello
```
This will produce an executable `say_hello`, which can be run with
```sh
./say_hello
```
to print the greeting to the console.
