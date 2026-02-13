module hello_mod
  implicit none

  contains

    subroutine say_hello() bind(C)
      implicit none
      print *, "Hello from Fortran!"
    end subroutine say_hello

end module hello_mod
