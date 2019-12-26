#include "Python.h"
#include "np_array.h"
#include "py_examples.h"

static PyMethodDef methods[] = {
  {"_examples_array",  py_examples_array, METH_VARARGS,
   "_examples_array(a, x)"},
  {"_examples_class_alloc",  py_examples_class_alloc, METH_VARARGS,
   "_examples_class_alloc()"},

  {NULL, NULL, 0, NULL}
};


static struct PyModuleDef module = {
  PyModuleDef_HEAD_INIT,
  "_templatelib", // name of this module
  "A template for Python package", // Doc String
  -1,
  methods
};

PyMODINIT_FUNC
PyInit__templatelib(void) {
  np_array::module_init();
  
  return PyModule_Create(&module);
}
