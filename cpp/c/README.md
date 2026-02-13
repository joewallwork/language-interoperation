# C++ to C

Calling C from C++ is simple because C is a strict subset of C++. As such,
anything contained in the C code can be directly used.

The C code in `hello.c` provides a simple greeting function:
```c
#include <stdio.h>

void say_hello() {
    printf("Hello from C!\n");
}
```
We don't actually need to compile this because this is such a minimal example
that we can just include the source directly in `hello.cpp`:
```cpp
#include "hello.c"

int main() {
    say_hello();
}
```
We can compile the program with the GNU C++ compiler `g++`:
```sh
g++ hello.cpp -o hello
```
Run the example with
```sh
./hello
```
