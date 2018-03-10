%typemap(out) float [ANY] {
  int i;
  $result = PyList_New($1_dim0);
  for (i = 0; i < $1_dim0; i++) {
    PyObject *o = PyFloat_FromDouble((double) $1[i]);
    PyList_SetItem($result, i, o);
  }
}

%typemap(out) float* AngularInfo::__iter__{
  int i;
  //$1, $1_dim0, $1_dim1
  $result = PyList_New(6);
  for (i = 0; i < 6; i++) {
    PyObject *o = PyFloat_FromFloat( $1[i]);
    PyList_SetItem($result,i,o);
  }
}
