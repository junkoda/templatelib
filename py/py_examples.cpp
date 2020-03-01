#include <vector>
#include <cassert>
#include "error.h"
#include "py_examples.h"
#include "py_buffer.h"

static void py_examples_class_free(PyObject *obj);

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
    // A class wraping `Buffer protocol` implemented in py_buffer.h
    Buffer<double> buf(py_array, "py_array"); // May throw TypeError

    if(buf.ndim != 1) {
      PyErr_SetString(PyExc_TypeError, "Exptected a 1-dim array");
      throw TypeError();
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
public:
  Class();

  std::vector<double> v;
};

Class::Class() : v({1.0, 3.0, 5.0})
{
  
}

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

PyObject* py_examples_class_len(PyObject* self, PyObject* args)
{
  PyObject *py_class;
  if(!PyArg_ParseTuple(args, "O", &py_class)) {
    return NULL;
  }

  Class* const c = (Class*) PyCapsule_GetPointer(py_class, "_Class");
  assert(c);

  return Py_BuildValue("k", static_cast<unsigned long>(c->v.size()));
}

PyObject* py_examples_class_getitem(PyObject* self, PyObject* args)
{
  PyObject *py_class;
  int i;
  if(!PyArg_ParseTuple(args, "Oi", &py_class, &i)) {
    return NULL;
  }

  Class* const c = (Class*) PyCapsule_GetPointer(py_class, "_Class");
  assert(c);

  if(0 <= i && i < static_cast<int>(c->v.size())) {
    return Py_BuildValue("d", c->v[i]);
  }

  // Python standard exceptions
  // https://docs.python.org/3/c-api/exceptions.html
  PyErr_SetNone(PyExc_IndexError);
  return NULL;
}


