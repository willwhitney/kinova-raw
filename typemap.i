
/* %define ARRAY_TO_LIST(type, name)
%typemap(out) type name[ANY] {
  $result = PyList_New($1_dim0);
  for(int i = 0; i < $1_dim0; i++) {
    PyList_SetItem($result, i, PyInt_FromLong($1[i]));
  } // i
}
%enddef */


%typemap(out) float [ANY] {
  int i;
  $result = PyList_New($1_dim0);
  for (i = 0; i < $1_dim0; i++) {
    PyObject *o = PyFloat_FromDouble((double) $1[i]);
    PyList_SetItem($result, i, o);
  }
}

/* %typemap(out) CartesianInfo [ANY] {
  int i;
  $result = PyList_New($1_dim0);
  for (i = 0; i < $1_dim0; i++) {
    CartesianInfo *o = $1[i];
    PyList_SetItem($result, i, o);
  }
} */

/* %typemap(out) CartesianInfo [ANY] {
} */
/* ARRAY_TO_LIST(CartesianInfo, CartesianInfo); */

%typemap(out) float* AngularInfo::__iter__{
  int i;
  //$1, $1_dim0, $1_dim1
  $result = PyList_New(6);
  for (i = 0; i < 6; i++) {
    PyObject *o = PyFloat_FromFloat( $1[i]);
    PyList_SetItem($result,i,o);
  }
}

%typemap(out) Zone* ZoneList::Zones{
  int i;
  //$1, $1_dim0, $1_dim1
  $result = PyList_New(6);
  for (i = 0; i < 6; i++) {
    PyObject *o = PyFloat_FromFloat( $1[i]);
    PyList_SetItem($result,i,o);
  }
}
