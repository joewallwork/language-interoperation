# Converting from Celsius to Fahrenheit

It's a happy coincidence that C and Fortran start with the same initials as the
units in everyone's favourite temperature conversion: Celsius and Fahrenheit!
Let's start off with a simple function that implements this conversion in C,
which can be found in `c2f.c`:
```c
float celsius2fahrenheit(float celsius) {
  return 9.0 * celsius / 5.0 + 32.0;
}
```
We can compile this with the GNU C compiler `gcc` with
```sh
gcc -c c2f.c -o c2f.o
```
This produces a binary file `example.o`. Simple so far.

The Fortran interface requires more work. The essential ingredient is the
`iso_c_binding` module, which has been intrinsic to Fortran standards since
2003. Its purpose is to provide inter-operation functionality with C. Since our
function's arguments and return values are both of `float` type, we can get away
with only importing the `c_float` kind:
```fortran
use, intrinsic :: iso_c_binding, only: c_float
```

To make the C function available in Fortran, we need to declare an interface for
it. This involves writing a Fortran function, which provides the signature of
the C function and how it should be called. The interface block looks like this:
```fortran
interface
  function celsius2fahrenheit_c(celsius_c) result(fahrenheit_c) &
      bind(c, name = 'celsius2fahrenheit')
    use, intrinsic :: iso_c_binding, only: c_float
    implicit none
    real(c_float), value, intent(in) :: celsius_c
    real(c_float) :: fahrenheit_c
  end function celsius2fahrenheit_c
end interface
```
Things to note are that the celsius argument is passed by value, which is the
default in C, that the return value is declared as a function result, and that
the `bind` attribute specifies the name of the C function to link against. The
`bind(c)` attribute is of crucial importance when interfacing between Fortran
and C (in both directions). Also note that the real variables declared for the
argument and return value use the `c_float` kind, to ensure compatibility.

With the interface defined as `celsius2fahrenheit_c`, we can now call the C
function from Fortran. Given variables `celsius` and `fahrenheit` of type
`real(c_float)`, we can call the function as follows:
```fortran
fahrenheit = celsius2fahrenheit_c(celsius)
```

See `c2f.f90` for the complete Fortran code for the conversion, including a user
input prompt. The Fortran code can be compiled with the GNU Fortran compiler `gfortran` as follows:
```sh
gfortran c2f.o c2f.f90 -o c2f
```
where we link to the object file `c2f.o` containing the compiled C code. Run the
example with
```sh
./c2f
```
