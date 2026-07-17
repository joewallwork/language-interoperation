// Python includes
// See: https://docs.python.org/3/extending/extending.html#a-simple-example
#define PY_SSIZE_T_CLEAN
#include <Python.h>

// Define function for saying hello in C++
// TODO: Avoid passing args - needs appropriate METH_X
static PyObject *hello(PyObject * /*self*/, PyObject *args) {
  // Doc: https://docs.python.org/3/c-api/sys.html#c.PySys_WriteStdout
  PySys_WriteStdout("Hello from C!\n");
  Py_RETURN_NONE;
}

// Define module methods
static PyMethodDef hello_methods[] = {
    {"hello", hello,
     // https://docs.python.org/3/c-api/structures.html#c.METH_VARARGS
     METH_VARARGS, // <- This indicates function takes a Tuple as argument
     "Say hello from C!\n\nHere is the docstring."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

// Define module
// Doc: https://docs.python.org/3/c-api/module.html#c.PyModuleDef
static struct PyModuleDef hello_module_def = {
    PyModuleDef_HEAD_INIT,         // Magic macro that handles Python internals
    "hello",                       // Module name
    "\"Say hello from C\" module", // Module docstring
    -1,                            // Set to -1 for 'single pass initialisation'
    hello_methods,                 // Provide list of methods module contains
    NULL,                          // Non null only in multi-pass initialisation
    NULL,                          // Function slots for deconstruction
    NULL,
    NULL};

// Note that we are using a legacy 'single-phase' initialisation
// https://docs.python.org/3/c-api/extension-modules.html#legacy-single-phase-initialization
PyMODINIT_FUNC PyInit_hello(void) { return PyModule_Create(&hello_module_def); }
