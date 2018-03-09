/*****************************************************************************************************/
/*                                                                                                   */
/* Uses the 7 dof robot and Ethernet in Cartesian mode                                               */
/*                                                                                                   */
/*****************************************************************************************************/

#include <iostream>
#include <dlfcn.h>
#include <vector>
#include "../../../API/EthCommandLayerUbuntu/Projects/Eclipse/Kinova.API.EthCommLayerUbuntu.h"
#include "../../../API/EthCommandLayerUbuntu/Projects/Eclipse/Kinova.API.EthCommandLayerUbuntu.h"
#include "../../../API/EthCommandLayerUbuntu/Projects/Eclipse/KinovaTypes.h"
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main()
{
	int result;

	//Handle for the library's command layer.
	void * commandLayer_handle;

	//Function pointers to the functions we need
	int (*MyInitAPI)();
	int (*MyCloseAPI)();
	int (*MyRefresDevicesList)();
	int (*MyMoveHome)();
	int (*MyInitFingers)();
	int (*MySetCartesianControl)();
	int (*MySetAngularControl)();
	int (*MySendBasicTrajectory)(TrajectoryPoint trajectory);
	int (*MySendAdvanceTrajectory)(TrajectoryPoint trajectory);
	int (*MyGetCartesianPosition)(CartesianPosition& pt);
	int (*MyGetAngularPosition)(AngularPosition& pt);
	int (*MyGetDevices)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result);
	int (*MySetActiveDevice)(KinovaDevice device);

	//We load the library
	commandLayer_handle = dlopen("Kinova.API.EthCommandLayerUbuntu.so",RTLD_NOW|RTLD_GLOBAL);

	//We load the functions from the library
	MyInitAPI 				= (int (*)()) dlsym(commandLayer_handle,"Ethernet_InitAPI");
	MyCloseAPI 				= (int (*)()) dlsym(commandLayer_handle,"Ethernet_CloseAPI");
	MyRefresDevicesList 	= (int (*)()) dlsym(commandLayer_handle,"Ethernet_RefresDevicesList");
	MyMoveHome 				= (int (*)()) dlsym(commandLayer_handle,"Ethernet_MoveHome");
	MyInitFingers 			= (int (*)()) dlsym(commandLayer_handle,"Ethernet_InitFingers");
	MySetCartesianControl 	= (int (*)()) dlsym(commandLayer_handle,"Ethernet_SetCartesianControl");
	MySetAngularControl 	= (int (*)()) dlsym(commandLayer_handle,"Ethernet_SetAngularControl");
	MySendBasicTrajectory 	= (int (*)(TrajectoryPoint trajectory)) dlsym(commandLayer_handle,"Ethernet_SendBasicTrajectory");
	MySendAdvanceTrajectory = (int (*)(TrajectoryPoint trajectory)) dlsym(commandLayer_handle,"Ethernet_SendAdvanceTrajectory");
	MyGetCartesianPosition 	= (int (*)(CartesianPosition& pt)) dlsym(commandLayer_handle,"Ethernet_GetCartesianPosition");
	MyGetAngularPosition 	= (int (*)(AngularPosition& pt)) dlsym(commandLayer_handle,"Ethernet_GetAngularPosition");
	MyGetDevices 			= (int (*)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result)) dlsym(commandLayer_handle,"Ethernet_GetDevices");
	MySetActiveDevice 		= (int (*)(KinovaDevice devices)) dlsym(commandLayer_handle,"Ethernet_SetActiveDevice");


	//If the was loaded correctly
	if((MyInitAPI == NULL) 				|| (MyCloseAPI == NULL) 		   || (MyGetDevices == NULL) 			||
	   (MyMoveHome == NULL) 			|| (MyInitFingers == NULL) 		   || (MySetCartesianControl == NULL) 	||
	   (MySetAngularControl== NULL) 	|| (MySendBasicTrajectory == NULL) || (MySendAdvanceTrajectory == NULL) ||
	   (MyGetCartesianPosition == NULL) || (MySetActiveDevice == NULL) 	   || (MyGetAngularPosition == NULL))
	{
		wcout << "* * *  E R R O R   D U R I N G   I N I T I A L I Z A T I O N  * * *" << endl;
	}
	else
	{
		wcout << "I N I T I A L I Z A T I O N   C O M P L E T E D" << endl << endl;

		result = (*MyInitAPI)();

		(*MyRefresDevicesList)();

		wcout << "Initialization's result :" << result << endl;

		KinovaDevice list[MAX_KINOVA_DEVICE];
		TrajectoryPoint command;
		CartesianPosition CartPos;
		AngularPosition AngPos;

		int devicesCount = MyGetDevices(list, result);

		for(int i = 0; i < devicesCount; i++)
		{
			wcout << "Found a robot on the network (" << list[i].SerialNumber << ")" << endl;

			//Setting the current device as the active device.
			MySetActiveDevice(list[i]);

			(*MyMoveHome)();
			(*MyInitFingers)(); //initializations

			(*MySetCartesianControl)();

			//get the current Cartesian position
			(*MyGetCartesianPosition)(CartPos);

			// first command: Cartesian Position: 10 cm above the current Cartesian position
			command.InitStruct();
			command.Position.CartesianPosition.X=CartPos.Coordinates.X;
			command.Position.CartesianPosition.Y=CartPos.Coordinates.Y;
			command.Position.CartesianPosition.Z=CartPos.Coordinates.Z+0.1;
			command.Position.CartesianPosition.ThetaX=CartPos.Coordinates.ThetaX;
			command.Position.CartesianPosition.ThetaY=CartPos.Coordinates.ThetaY;
			command.Position.CartesianPosition.ThetaZ=CartPos.Coordinates.ThetaZ;

			//add a velocity limitation
			command.Limitations.speedParameter1=0.10; // translation limited to 0.10 m/sec
			command.Limitations.speedParameter2=0.5; //rotation limited to 05. rad/sec
			command.Limitations.speedParameter3=0; //speed parameter for the fingers. Not considered in the trajectory functions

			//enable limitations
			command.LimitationsActive=1;

			command.Position.HandMode=HAND_NOMOVEMENT; // no movement from the fingers

			command.Position.Type=CARTESIAN_POSITION;

			//send the command
			(*MySendAdvanceTrajectory)(command);
			usleep(2000);

			//now lets send Cartesian velocity commands: motion in X for 4 seconds at 15 cm/sec
			// + rotation around effector's X axis for last 2 sec at 0.75 rad/sec
			command.InitStruct();
			command.Position.CartesianPosition.X=0.15;
			command.Position.CartesianPosition.Y=0;
			command.Position.CartesianPosition.Z=0;
			command.Position.CartesianPosition.ThetaX=0;
			command.Position.CartesianPosition.ThetaY=0;
			command.Position.CartesianPosition.ThetaZ=0;

			command.Position.HandMode=HAND_NOMOVEMENT; // no movement from the fingers

			command.Position.Type=CARTESIAN_VELOCITY;

			//send the command
			for (int p=0; p<200; p++)
			{
				(*MySendAdvanceTrajectory)(command);
				usleep(6000);
			}

			command.Position.CartesianPosition.ThetaX=0.75;

			//send the command
			for (int p=0; p<200; p++)
			{
				(*MySendAdvanceTrajectory)(command);
				usleep(6000);
			}

			//now switch to angular mode
			(*MySetAngularControl)();

			//get current angular position
			(*MyGetAngularPosition)(AngPos);

			//send angular position command: +90 degrees on joint 7
			command.InitStruct();
			command.Position.Actuators.Actuator1=AngPos.Actuators.Actuator1;
			command.Position.Actuators.Actuator2=AngPos.Actuators.Actuator2;
			command.Position.Actuators.Actuator3=AngPos.Actuators.Actuator3;
			command.Position.Actuators.Actuator4=AngPos.Actuators.Actuator4;
			command.Position.Actuators.Actuator5=AngPos.Actuators.Actuator5;
			command.Position.Actuators.Actuator6=AngPos.Actuators.Actuator6;
			command.Position.Actuators.Actuator7=AngPos.Actuators.Actuator7+90.0;

			//add a velocity limitation
			command.Limitations.speedParameter1=30; // rotation velocity of 4 first joints (3 for a 6 dof robot) limited to 30 deg/sec
			command.Limitations.speedParameter2=40.0; // rotation velocity of 3 last joints limited to 40 deg /sec
			command.Limitations.speedParameter3=0; //speed parameter for the fingers. Not considered in the trajectory functions

			//enable limitations
			command.LimitationsActive=1;

			command.Position.Type=ANGULAR_POSITION;

			//send the command
			(*MySendAdvanceTrajectory)(command);
			usleep(2000);

		}

		result = (*MyCloseAPI)();
	}

	dlclose(commandLayer_handle);

	return 0;
}
