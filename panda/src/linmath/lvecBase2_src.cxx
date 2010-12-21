// Filename: lvecBase2_src.cxx
// Created by:  drose (08Mar00)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////

TypeHandle FLOATNAME(LVecBase2)::_type_handle;

#ifdef HAVE_PYTHON
#include "py_panda.h"  

#ifndef CPPPARSER
IMPORT_THIS struct Dtool_PyTypedObject FLOATNAME(Dtool_LVecBase2);
#endif
#endif  // HAVE_PYTHON

const FLOATNAME(LVecBase2) FLOATNAME(LVecBase2)::_zero =
  FLOATNAME(LVecBase2)(0.0f, 0.0f);
const FLOATNAME(LVecBase2) FLOATNAME(LVecBase2)::_unit_x =
  FLOATNAME(LVecBase2)(1.0f, 0.0f);
const FLOATNAME(LVecBase2) FLOATNAME(LVecBase2)::_unit_y =
  FLOATNAME(LVecBase2)(0.0f, 1.0f);

#ifdef HAVE_PYTHON
////////////////////////////////////////////////////////////////////
//     Function: LVecBase2::__reduce__
//       Access: Published
//  Description: This special Python method is implement to provide
//               support for the pickle module.
////////////////////////////////////////////////////////////////////
PyObject *FLOATNAME(LVecBase2)::
__reduce__(PyObject *self) const {
  // We should return at least a 2-tuple, (Class, (args)): the
  // necessary class object whose constructor we should call
  // (e.g. this), and the arguments necessary to reconstruct this
  // object.
  PyObject *this_class = PyObject_Type(self);
  if (this_class == NULL) {
    return NULL;
  }

  PyObject *result = Py_BuildValue("(O(ff))", this_class, 
                                   (*this)[0], (*this)[1]);
  Py_DECREF(this_class);
  return result;
}

////////////////////////////////////////////////////////////////////
//     Function: LVecBase2::__getattr__
//       Access: Published
//  Description: This is used to implement swizzle masks.
////////////////////////////////////////////////////////////////////
PyObject *FLOATNAME(LVecBase2)::
__getattr__(const string &attr_name) const {
#ifndef NDEBUG
  // Validate the attribute name.
  for (string::const_iterator it = attr_name.begin(); it < attr_name.end(); it++) {
    if (*it != 'x' && *it != 'y') {
      return NULL;
    }
  }
#endif

  if (attr_name.size() == 1) {
    return PyFloat_FromDouble(_v.data[attr_name[0] - 'x']);

  } else if (attr_name.size() == 2) {
    FLOATNAME(LVecBase2) *vec = new FLOATNAME(LVecBase2);
    vec->_v.v._0 = _v.data[attr_name[0] - 'x'];
    vec->_v.v._1 = _v.data[attr_name[1] - 'x'];
    return DTool_CreatePyInstance((void *)vec, FLOATNAME(Dtool_LVecBase2), true, false);
  }

  return NULL;
}

////////////////////////////////////////////////////////////////////
//     Function: LVecBase2::__setattr__
//       Access: Published
//  Description: This is used to implement write masks.
////////////////////////////////////////////////////////////////////
int FLOATNAME(LVecBase2)::
__setattr__(PyObject *self, const string &attr_name, FLOATTYPE val) {
#ifndef NDEBUG
  // Loop through the components in the attribute name,
  // and assign the floating-point value to every one of them.
  for (string::const_iterator it = attr_name.begin(); it < attr_name.end(); it++) {
    if ((*it) != 'x' && (*it) != 'y') {
      PyTypeObject *tp = Py_TYPE(self);
      PyErr_Format(PyExc_AttributeError,
                   "'%.100s' object has no attribute '%.200s'",
                   tp->tp_name, attr_name.c_str());
      return -1;
    }

    _v.data[(*it) - 'x'] = val;
  }
#endif

  return 0;
}

////////////////////////////////////////////////////////////////////
//     Function: LVecBase2::__setattr__
//       Access: Published
//  Description: This is used to implement write masks.
////////////////////////////////////////////////////////////////////
int FLOATNAME(LVecBase2)::
__setattr__(PyObject *self, const string &attr_name, FLOATNAME(LVecBase2) val) {
#ifndef NDEBUG
  // Validate the attribute name.
  if (attr_name == "x" || attr_name == "y") {
    PyErr_SetString(PyExc_ValueError, "a float is required");
    return -1;
  }
  if (attr_name != "xy" && attr_name != "yx") {
    PyTypeObject *tp = Py_TYPE(self);
    PyErr_Format(PyExc_AttributeError,
                 "'%.100s' object has no attribute '%.200s'",
                 tp->tp_name, attr_name.c_str());
    return -1;
  }
#endif

  _v.data[attr_name[0] - 'x'] = val._v.v._0;
  _v.data[attr_name[1] - 'x'] = val._v.v._1;
  return 0;
}
#endif  // HAVE_PYTHON

////////////////////////////////////////////////////////////////////
//     Function: LVecBase2::init_type
//       Access: Public, Static
//  Description:
////////////////////////////////////////////////////////////////////
void FLOATNAME(LVecBase2)::
init_type() {
  if (_type_handle == TypeHandle::none()) {
    // Format a string to describe the type.
    string name = "LVecBase2";
    name += FLOATTOKEN;
    register_type(_type_handle, name);
  }
}
