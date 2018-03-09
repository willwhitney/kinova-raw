%module kinova_raw
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

%extend AngularInfo {
  char *__str__() {
    static char tmp[512];
    snprintf(tmp, 512, "[%f, %f, %f, %f, %f, %f]",
      self->Actuator1,
      self->Actuator2,
      self->Actuator3,
      self->Actuator4,
      self->Actuator5,
      self->Actuator6
    );
    return tmp;
  }
}

%extend AngularPosition {
  char *__str__() {
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

%extend CartesianInfo {
  char *__str__() {
    static char tmp[512];
    snprintf(tmp, 512, "[%f, %f, %f]",
      self->X,
      self->Y,
      self->Z
    );
    return tmp;
  }
}

%extend CartesianPosition {
  char *__str__() {
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
  char *__str__() {
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
  char *__str__() {
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
