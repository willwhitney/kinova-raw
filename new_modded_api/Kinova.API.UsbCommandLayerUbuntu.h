#ifdef KINOVAAPIUSBCOMMANDLAYER_EXPORTS
#define KINOVAAPIUSBCOMMANDLAYER_API 
#else
#define KINOVAAPIUSBCOMMANDLAYER_API
#endif

/**
 * @file Kinova.API.UsbCommandLayerUbuntu.h
 * @brief This file contains header of all available functions of this API.
 */

#include <vector>
#include "KinovaTypes.h"
#include "Kinova.API.CommLayerUbuntu.h"
#include <stdio.h>

//This defines the the location of the communication layer.(Kinova.API.CommLayerUbuntu.so)
#define COMM_LAYER_PATH "Kinova.API.CommLayerUbuntu.so"

// ***** E R R O R   C O D E S ******
#define ERROR_INIT_API 2001      // Error while initializing the API
#define ERROR_LOAD_COMM_DLL 2002 // Error while loading the communication layer

//Those 3 codes are mostly for internal use
#define JACO_NACK_FIRST 2003
#define JACO_COMM_FAILED 2004
#define JACO_NACK_NORMAL 2005

//Unable to initialize the communication layer.
#define ERROR_INIT_COMM_METHOD  2006

//Unable to load the Close() function from the communication layer.
#define ERROR_CLOSE_METHOD  2007

//Unable to load the GetDeviceCount() function from the communication layer.
#define ERROR_GET_DEVICE_COUNT_METHOD  2008

//Unable to load the SendPacket() function from the communication layer.
#define ERROR_SEND_PACKET_METHOD  2009

//Unable to load the SetActiveDevice() function from the communication layer.
#define ERROR_SET_ACTIVE_DEVICE_METHOD 2010

//Unable to load the GetDeviceList() function from the communication layer.
#define ERROR_GET_DEVICES_LIST_METHOD 2011

//Unable to initialized the system semaphore.
#define ERROR_SEMAPHORE_FAILED 2012

//Unable to load the ScanForNewDevice() function from the communication layer.
#define ERROR_SCAN_FOR_NEW_DEVICE 2013

//Unable to load the GetActiveDevice function from the communication layer.
#define ERROR_GET_ACTIVE_DEVICE_METHOD 2014

//A function's parameter is not valid.
#define ERROR_INVALID_PARAM 2100

//The API is not initialized.
#define ERROR_API_NOT_INITIALIZED 2101

//Unable to load the InitDataStructure() function from the communication layer.
#define ERROR_INIT_DATA_STRUCTURES_METHOD 2102

// ***** E N D  O F  E R R O R   C O D E S ******

//This represents the size of an array containing Cartesian values.
#define CARTESIAN_SIZE 6

//This represents the max actuator count in our context.
#define MAX_ACTUATORS 6

//This represents the max actuator count in our context.
#define MAX_INVENTORY 15

//This represents the size of the array returned by the function GetCodeVersion.
#define CODE_VERSION_COUNT 37

//This represents the size of the array returned by the function GetAPIVersion.
#define API_VERSION_COUNT 3

//This represents the size of the array returned by the function GetPositionCurrentActuators.
#define POSITION_CURRENT_COUNT 12

//This represents the size of the array returned by the function GetSpasmFilterValues and sent to SetSpasmFilterValues.
#define SPASM_FILTER_COUNT 1

//Version of the API 5.02.00
#define COMMAND_LAYER_VERSION 50200


// ***** API'S FUNCTIONAL CORE *****

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetDevices(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetActiveDevice(KinovaDevice device);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int RefresDevicesList(void);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int InitAPI(void);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int CloseAPI(void);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetCodeVersion(int Response[CODE_VERSION_COUNT]);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetAPIVersion(int Response[API_VERSION_COUNT]);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetCartesianPosition(CartesianPosition &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetAngularPosition(AngularPosition &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetCartesianForce(CartesianPosition &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetAngularForce(AngularPosition &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetAngularCurrent(AngularPosition &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetActualTrajectoryInfo(TrajectoryPoint &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetGlobalTrajectoryInfo(TrajectoryFIFO &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetSensorsInfo(SensorsInfo &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetSingularityVector(SingularityVector &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetAngularControl();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetCartesianControl();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int StartControlAPI();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int StopControlAPI();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int RestoreFactoryDefault();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SendJoystickCommand(JoystickCommand joystickCommand);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SendAdvanceTrajectory(TrajectoryPoint trajectory);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SendBasicTrajectory(TrajectoryPoint trajectory);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetClientConfigurations(ClientConfigurations &config);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetClientConfigurations(ClientConfigurations config);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int EraseAllTrajectories();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetPositionCurrentActuators(float Response[POSITION_CURRENT_COUNT]);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetActuatorPID(unsigned int address, float P, float I, float D);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetAngularCommand(AngularPosition &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetCartesianCommand(CartesianPosition &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetAngularCurrentMotor(AngularPosition &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetAngularVelocity(AngularPosition &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetControlType(int &Response);

// extern "C" KINOVAAPIUSBCOMMANDLAYER_API int StartForceControl();

// extern "C" KINOVAAPIUSBCOMMANDLAYER_API int StopForceControl();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int StartCurrentLimitation();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int StopCurrentLimitation();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetSystemErrorCount(unsigned int &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetSystemError(unsigned int indexError, SystemError &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int ClearErrorLog();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int EraseAllProtectionZones();

//Internal use only
extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetSerialNumber(char Command[STRING_LENGTH], char temp[STRING_LENGTH]);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetControlMapping(ControlMappingCharts &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetProtectionZone(ZoneList &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetProtectionZone(ZoneList Command);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetGripperStatus(Gripper &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetQuickStatus(QuickStatus &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetForcesInfo(ForcesInfo &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetControlMapping(ControlMappingCharts Command);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int ProgramFlash(const char * filename);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetJointZero(int ActuatorAdress);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetActuatorPIDFilter(int ActuatorAdress, float filterP, float filterI, float filterD);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetActuatorAddress(int ActuatorAdress, int newAddress);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetGeneralInformations(GeneralInformations &Response);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetSpasmFilterValues(float Command[SPASM_FILTER_COUNT], int activationStatus);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetSpasmFilterValues(float Response[SPASM_FILTER_COUNT], int &activationStatus);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int MoveHome();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int InitFingers();

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetPeripheralInventory(PeripheralInfo list[MAX_INVENTORY] );

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetJoystickValue(JoystickCommand &joystickCommand);

extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetCommandVelocity(float cartesianVelocity[CARTESIAN_SIZE], float angularVelocity[MAX_ACTUATORS]);

// extern "C" KINOVAAPIUSBCOMMANDLAYER_API int GetEndEffectorOffset(unsigned int &status, float &x, float &y, float &z);

// extern "C" KINOVAAPIUSBCOMMANDLAYER_API int SetEndEffectorOffset(unsigned int status, float x, float y, float z);


