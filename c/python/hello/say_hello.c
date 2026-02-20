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
