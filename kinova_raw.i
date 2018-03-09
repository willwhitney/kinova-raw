%module kinova_raw

%{
  /* #include <iostream> */
  /* #include <dlfcn.h> */
  /* #include <vector> */
  #include "KinovaTypes.h"
  #include "Kinova.API.CommLayerUbuntu.h"
  /* #include "Kinova.API.EthCommLayerUbuntu.h" */
  #include "Kinova.API.UsbCommandLayerUbuntu.h"
  /* #include "Kinova.API.EthCommandLayerUbuntu.h" */

%}
%include "KinovaTypes.h"
%include "Kinova.API.CommLayerUbuntu.h"
/* %include "Kinova.API.EthCommLayerUbuntu.h" */
%include "Kinova.API.UsbCommandLayerUbuntu.h"
/* %include "Kinova.API.EthCommandLayerUbuntu.h" */
/* extern "C" int GetDeviceCount(int &result); */

/* %import std_vector.i */
%include "std_vector.i"
// Instantiate templates used by example
namespace std {
   %template(IntVector) vector<int>;
   %template(DoubleVector) vector<double>;
   /* %template(FloatVector) vector<float>; */
}
%include "carrays.i"
%array_functions(float, floatArray);
