%module kinova_raw
%include typemap.i
%feature("autodoc", "1");

%{
  /* #include <iostream> */
  /* #include <dlfcn.h> */
  /* #include <vector> */
  #include "KinovaTypes.h"
  #include "Kinova.API.CommLayerUbuntu.h"
  /* #include "Kinova.API.EthCommLayerUbuntu.h" */
  #include "Kinova.API.UsbCommandLayerUbuntu.h"
  /* #include "Kinova.API.EthCommandLayerUbuntu.h" */
  /* void print_array(float arr[6]); */

  static int INDEX_EXCEPT = 0; // flag to save error state
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
%array_class(float, FloatArray);
%include "exception.i"
/* %array_functions(float, floatArray); */
/* void print_array(float arr[6]) {
  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 6; j++) {
        printf("%f ", arr[i][j]);
    }
    printf("\n");
  }
} */


%exception AngularInfo::__getitem__ {
  assert(!INDEX_EXCEPT);
  $action
  if (INDEX_EXCEPT) {
    INDEX_EXCEPT = 0; // clear flag for next time
    SWIG_exception(SWIG_IndexError, "Index out of bounds");
  }
}

%exception AngularInfo::__setitem__ {
  assert(!INDEX_EXCEPT);
  $action
  if (INDEX_EXCEPT) {
    INDEX_EXCEPT = 0; // clear flag for next time
    SWIG_exception(SWIG_IndexError, "Index out of bounds");
  }
}

%extend AngularInfo {
  char *__repr__() {
    static char tmp[512];
    snprintf(tmp, 512, "AngularInfo [%f, %f, %f, %f, %f, %f]",
      self->Actuator1,
      self->Actuator2,
      self->Actuator3,
      self->Actuator4,
      self->Actuator5,
      self->Actuator6
    );
    return tmp;
  }

  int __len__() {
    return 6;
  }

  float __getitem__(int i) {
    switch (i) {
      case 0:
      return self->Actuator1;
      break;
      case 1:
      return self->Actuator2;
      break;
      case 2:
      return self->Actuator3;
      break;
      case 3:
      return self->Actuator4;
      break;
      case 4:
      return self->Actuator5;
      break;
      case 5:
      return self->Actuator6;
      break;

      default:
      INDEX_EXCEPT = 1;
      return 0;
    }
  }

  void __setitem__(int i, float angle) {
    switch (i) {
      case 0:
      self->Actuator1 = angle;
      break;
      case 1:
      self->Actuator2 = angle;
      break;
      case 2:
      self->Actuator3 = angle;
      break;
      case 3:
      self->Actuator4 = angle;
      break;
      case 4:
      self->Actuator5 = angle;
      break;
      case 5:
      self->Actuator6 = angle;
      break;

      default:
      INDEX_EXCEPT = 1;
      return;
    }
  }
}



%extend AngularPosition {
  char *__repr__() {
    static char tmp[512];
    snprintf(tmp, 512, "<kinovapy.AngularPosition> Actuators: [%f, %f, %f, %f, %f, %f], Fingers: [%f, %f, %f]",
      self->Actuators.Actuator1,
      self->Actuators.Actuator2,
      self->Actuators.Actuator3,
      self->Actuators.Actuator4,
      self->Actuators.Actuator5,
      self->Actuators.Actuator6,
      self->Fingers.Finger1,
      self->Fingers.Finger2,
      self->Fingers.Finger3
    );
    return tmp;
  }
}

%exception FingersPosition::__getitem__ {
  assert(!INDEX_EXCEPT);
  $action
  if (INDEX_EXCEPT) {
    INDEX_EXCEPT = 0; // clear flag for next time
    SWIG_exception(SWIG_IndexError, "Index out of bounds");
  }
}

%exception FingersPosition::__setitem__ {
  assert(!INDEX_EXCEPT);
  $action
  if (INDEX_EXCEPT) {
    INDEX_EXCEPT = 0; // clear flag for next time
    SWIG_exception(SWIG_IndexError, "Index out of bounds");
  }
}

%extend FingersPosition {
  char *__repr__() {
    static char tmp[512];
    snprintf(tmp, 512, "[%f, %f, %f]",
      self->Finger1,
      self->Finger2,
      self->Finger3
    );
    return tmp;
  }

  int __len__() {
    return 3;
  }

  float __getitem__(int i) {
    switch (i) {
      case 0:
      return self->Finger1;
      break;
      case 1:
      return self->Finger2;
      break;
      case 2:
      return self->Finger3;
      break;

      default:
      INDEX_EXCEPT = 1;
      return 0;
    }
  }

  void __setitem__(int i, float position) {
    switch (i) {
      case 0:
      self->Finger1 = position;
      break;
      case 1:
      self->Finger2 = position;
      break;
      case 2:
      self->Finger3 = position;
      break;

      default:
      INDEX_EXCEPT = 1;
      return;
    }
  }
}

%exception CartesianInfo::__getitem__ {
  assert(!INDEX_EXCEPT);
  $action
  if (INDEX_EXCEPT) {
    INDEX_EXCEPT = 0; // clear flag for next time
    SWIG_exception(SWIG_IndexError, "Index out of bounds");
  }
}

%exception CartesianInfo::__setitem__ {
  assert(!INDEX_EXCEPT);
  $action
  if (INDEX_EXCEPT) {
    INDEX_EXCEPT = 0; // clear flag for next time
    SWIG_exception(SWIG_IndexError, "Index out of bounds");
  }
}

%extend CartesianInfo {
  char *__repr__() {
    static char tmp[512];
    snprintf(tmp, 512, "CartesianInfo [%f, %f, %f], angles [%f, %f, %f]",
      self->X,
      self->Y,
      self->Z,
      self->ThetaX,
      self->ThetaY,
      self->ThetaZ
    );
    return tmp;
  }

  int __len__() {
    return 3;
  }

  float __getitem__(int i) {
    switch (i) {
      case 0:
      return self->X;
      break;
      case 1:
      return self->Y;
      break;
      case 2:
      return self->Z;
      break;

      default:
      INDEX_EXCEPT = 1;
      return 0;
    }
  }

  void __setitem__(int i, float position) {
    switch (i) {
      case 0:
      self->X = position;
      break;
      case 1:
      self->Y = position;
      break;
      case 2:
      self->Z = position;
      break;

      default:
      INDEX_EXCEPT = 1;
      return;
    }
  }
}

%extend CartesianPosition {
  char *__repr__() {
    static char tmp[512];
    snprintf(tmp, 512, "<kinovapy.CartesianPosition> Coordinates: Position: [%f, %f, %f], Orientation: [%f, %f, %f], Fingers: [%f, %f, %f]",
      self->Coordinates.X,
      self->Coordinates.Y,
      self->Coordinates.Z,
      self->Coordinates.ThetaX,
      self->Coordinates.ThetaY,
      self->Coordinates.ThetaZ,
      self->Fingers.Finger1,
      self->Fingers.Finger2,
      self->Fingers.Finger3
    );
    return tmp;
  }
}

%extend QuickStatus {
  char *__repr__() {
    static char tmp[512];
    snprintf(tmp, 512, "<kinovapy.QuickStatus> Fingers: (%d, %d, %d), ControlEnable: %d, ControlModule: %d, ControlFrame: %d, CartesianFault: %d, ForceControl: %d, CurrentLimit: %d, RobotType: %d, TorqueSensors: %d",
      self->Finger1Status, self->Finger2Status, self->Finger3Status,
      self->ControlEnableStatus, self->ControlActiveModule,
      self->ControlFrameType, self->CartesianFaultState,
      self->ForceControlStatus, self->CurrentLimitationStatus,
      self->RobotType, self->TorqueSensorsStatus
    );
    return tmp;
  }
}


%extend ForcesInfo {
  char *__repr__() {
    static char tmp[512];
    const float thresh = 0.1;
    snprintf(tmp, 512, "actuator_forces: [%f, %f, %f, %f, %f, %f], 'cartesian_forces: [%f, %f, %f, %f, %f, %f]",
      self->Actuator1 > thresh ? self->Actuator1 : 0,
      self->Actuator2 > thresh ? self->Actuator2 : 0,
      self->Actuator3 > thresh ? self->Actuator3 : 0,
      self->Actuator4 > thresh ? self->Actuator4 : 0,
      self->Actuator5 > thresh ? self->Actuator5 : 0,
      self->Actuator6 > thresh ? self->Actuator6 : 0,
      self->X > thresh ? self->X : 0,
      self->Y > thresh ? self->Y : 0,
      self->Z > thresh ? self->Z : 0,
      self->ThetaX > thresh ? self->ThetaX : 0,
      self->ThetaY > thresh ? self->ThetaY : 0,
      self->ThetaZ > thresh ? self->ThetaZ : 0
    );
    return tmp;
  }
}
