#include <cassert>
#include "error.h"
#include "py_examples.h"
#include "py_buffer.h"

//
// py_examples_array
//
PyObject* py_examples_array(PyObject* self, PyObject* args)
{
  // _examples_array(a, x)
  // Add a float x to all elements in array a
  PyObject *py_array;
  double x;
  //
  // https://docs.python.org/3/c-api/arg.html
  // e.g., d for double, i for integer
  //
  if(!PyArg_ParseTuple(args, "Od", &py_array, &x)) {
    return NULL;
  }

  try {
    // Buffer template class is defined in py_buffer.h
    Buffer<double> buf(py_array, "py_array"); // May throw TypeError

    if(buf.ndim != 1) {
      PyErr_SetString(PyExc_TypeError, "Exptected a 1-dim array");
      return NULL;
    }

    const size_t n = buf.shape[0];
    
    for(size_t i=0; i<n; ++i)
      buf(i) += x;
      // Buffer can also handle 2-dimensional array buf(i, j) if buf.ndim == 2
  }
  catch(TypeError) {
    return NULL;
  }
    

  Py_RETURN_NONE;
}



//
// Example wrapping a C++ class
//
class Class {

};

static void py_examples_class_free(PyObject *obj);

PyObject* py_examples_class_alloc(PyObject* self, PyObject* args)
{
  // _watershed_alloc()
  // Create a new watershed object
  Class* const c = new Class();

  return PyCapsule_New(c, "_Class", py_examples_class_free);
}

void py_examples_class_free(PyObject *obj)
{
  // Delete Watershed object, called automatically by Python
  Class* const c = (Class*) PyCapsule_GetPointer(obj, "_Class");
  assert(c);

  delete c;
}

