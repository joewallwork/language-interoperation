# Hello, World!

Calling C from C++ is simple because C is a strict subset of C++. As such,
anything contained in the C code can be directly used. The only real
complication is that C function declarations require the `extern "C"`
preprocessor directive, for reasons detailed below.

When you compile C++ code, the compiler mangles function names to support
overloading. However, C doesn't use name mangling. To link C and C++ code
together, you must tell the C++ compiler to use C linkage for C functions.
The C header file `hello.h` provides this:
```c
#ifdef __cplusplus
extern "C" {
#endif

void say_hello(void);

#ifdef __cplusplus
}
#endif
```
This conditional compilation pattern ensures:
- When included in C++ code, the `extern "C"` block prevents name mangling
- When included in C code, the `#ifdef __cplusplus` is false, so it has no effect

The C code in `hello.c` includes the header and provides the implementation:
```c
#include "hello.h"
#include <stdio.h>

void say_hello(void) {
    printf("Hello from C!\n");
}
```
This can be compiled with the GNU C compiler `gcc` with
```sh
gcc -c hello.c -o hello.o
```

The C++ code in `hello.cpp` includes the header and calls the C function:
```cpp
#include "hello.h"

int main() {
    say_hello();
    return 0;
}
```
This can be compiled with the GNU C++ compiler `g++` with
```sh
g++ hello.o hello.cpp -o hello
```
Run it with
```sh
./hello
```

## Key Points

- **Never include .c files in C++ code** - always use proper headers.
- **Always use `extern "C"` guards** in C headers for C/C++ inter-operation.
- **Compile separately** - compile C code as C, C++ code as C++, then link.
- **Without `extern "C"`** you get undefined reference linker errors.
