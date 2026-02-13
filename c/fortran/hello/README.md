# Hello, World!

Where else to start but with a good old "Hello, World!" example? The Fortran
code in `hello.f90` provides a module containing a single subroutine. That
subroutine takes no arguments and simply prints a greeting to the console.
```fortran
subroutine say_hello() bind(C)
  implicit none
  print *, "Hello from Fortran!"
end subroutine say_hello
```
The only thing to note here is the use of `bind(C)`. This tells the Fortran
compiler to generate a C-compatible symbol for the subroutine, which allows us
to call it from C code. We can compile this with the GNU Fortran compiler
`gfortran` with
```sh
gfortran -c hello.f90 -o hello_f.o
```
This produces a binary file `hello_f.o`.

On the C-side (beside the C) we have a simple `main` function that calls the
Fortran subroutine. On its own, the `say_hello` function would be undefined, so
the final ingredient is to declare the `extern` function prototype for the
Fortran subroutine, so that it knows what it is. Note that this needs to be done
before it is used:
```c
extern void say_hello(void);

int main() {
  say_hello();
  return 0;
}
```
Similarly as above, we can compile the C code with the GNU C compiler `gcc` with
```sh
gcc -c hello.c -o hello_c.o
```

The final step is to link the two object files together to create an executable.
This can be done with
```sh
gcc hello_c.o hello_f.o -lgfortran -o hello
```
Note that we include the `-lgfortran` linker flag to link against the Fortran
runtime library. Run the example with
```sh
./hello
```
