program c2f
  use, intrinsic :: iso_c_binding, only: c_float

  implicit none

  real :: c

  write(*,*) "Enter a Celsius temperature:"
  read(*,*) c
  write(*,*) c, " -> ", celsius2fahrenheit(c)

  contains

    function celsius2fahrenheit(celsius) result(fahrenheit)
      real(c_float), intent(in) :: celsius
      real(c_float) :: fahrenheit

      interface
        function celsius2fahrenheit_c(celsius_c) result(fahrenheit_c) &
            bind(c, name = 'celsius2fahrenheit')
          use, intrinsic :: iso_c_binding, only: c_float
          implicit none
          real(c_float), value, intent(in) :: celsius_c
          real(c_float) :: fahrenheit_c
        end function celsius2fahrenheit_c
      end interface

      fahrenheit = celsius2fahrenheit_c(celsius)
    end function celsius2fahrenheit

end program c2f
