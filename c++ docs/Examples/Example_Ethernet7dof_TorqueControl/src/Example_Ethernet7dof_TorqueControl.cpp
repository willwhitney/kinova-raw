/*****************************************************************************************************/
/*                                                                                                   */
/* Uses the 7 dof robot and Ethernet in Torque mode with the optimal gravity compensation mode       */
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
#include <fstream>

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
	int (*MyRunGravityEstimationSequence7dof)(ROBOT_TYPE type, float OptimalzParam[OPTIMAL_Z_PARAM_SIZE_7DOF]);
	int (*MySetGravityType)(GRAVITY_TYPE type);
	int (*MySwitchTorque)(GENERALCONTROL_TYPE type);
	int (*MySendAngularTorqueCommand)(float Command[COMMAND_SIZE]);
	int (*MySendCartesianForceCommand)(float Command[COMMAND_SIZE]);
	int (*MyGetDevices)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result);
	int (*MySetActiveDevice)(KinovaDevice device);
	int (*MySetGravityOptimalZParam)(float Command[GRAVITY_PARAM_SIZE]);
	int (*MySetSafetyFactorTorque)(float factor);

	//We load the library
	commandLayer_handle = dlopen("Kinova.API.EthCommandLayerUbuntu.so",RTLD_NOW|RTLD_GLOBAL);

	cout << dlerror();

	//We load the functions from the library
	MyInitAPI = (int (*)()) dlsym(commandLayer_handle,"Ethernet_InitAPI");
	MyCloseAPI = (int (*)()) dlsym(commandLayer_handle,"Ethernet_CloseAPI");
	MyRefresDevicesList = (int (*)()) dlsym(commandLayer_handle,"Ethernet_RefresDevicesList");
	MyMoveHome = (int (*)()) dlsym(commandLayer_handle,"Ethernet_MoveHome");
	MyRunGravityEstimationSequence7dof = (int (*)(ROBOT_TYPE type, float OptimalzParam[OPTIMAL_Z_PARAM_SIZE_7DOF]))
			dlsym(commandLayer_handle,"Ethernet_RunGravityZEstimationSequence7DOF");
	MySetGravityType = (int (*)(GRAVITY_TYPE type)) dlsym(commandLayer_handle,"Ethernet_SetGravityType");
	MySwitchTorque = (int (*)(GENERALCONTROL_TYPE type)) dlsym(commandLayer_handle,"Ethernet_SwitchTrajectoryTorque");
	MySendAngularTorqueCommand = (int (*)(float Command[COMMAND_SIZE])) dlsym(commandLayer_handle,"Ethernet_SendAngularTorqueCommand");
	MySendCartesianForceCommand = (int (*)(float Command[COMMAND_SIZE])) dlsym(commandLayer_handle,"Ethernet_SendCartesianForceCommand");

	MyGetDevices = (int (*)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result)) dlsym(commandLayer_handle,"Ethernet_GetDevices");
	MySetActiveDevice = (int (*)(KinovaDevice devices)) dlsym(commandLayer_handle,"Ethernet_SetActiveDevice");

	MySetGravityOptimalZParam = (int (*)(float Command[GRAVITY_PARAM_SIZE])) dlsym(commandLayer_handle, "Ethernet_SetGravityOptimalZParam");
	MySetSafetyFactorTorque = (int (*)(float factor)) dlsym(commandLayer_handle, "Ethernet_SetTorqueSafetyFactor");

	//If the was loaded correctly
	if((MyInitAPI == NULL) || (MyCloseAPI == NULL) || (MyGetDevices == NULL) || (MyMoveHome == NULL)
	|| (MyRunGravityEstimationSequence7dof == NULL) || (MySetGravityType == NULL) || (MySwitchTorque== NULL)
	|| (MySendAngularTorqueCommand == NULL) || (MySendCartesianForceCommand == NULL) || (MySetActiveDevice == NULL)
	|| (MySetGravityOptimalZParam == NULL) || (MySetSafetyFactorTorque == NULL))
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
		wchar_t ansCalib;
		float OptimalzParam[OPTIMAL_Z_PARAM_SIZE_7DOF];

		float GravParamCommand[GRAVITY_PARAM_SIZE];
		for (int i =0; i<GRAVITY_PARAM_SIZE; i++)
		{
			GravParamCommand[i]=0.0; //initialization
		}


		float TorqueCommand[COMMAND_SIZE];
		for (int i =0; i<COMMAND_SIZE; i++)
		{
			TorqueCommand[i]=0.0; //initialization
		}


		int devicesCount = MyGetDevices(list, result);

		for(int i = 0; i < devicesCount; i++)
		{
			wcout << "Found a robot on the network (" << list[i].SerialNumber << ")" << endl;

			//Setting the current device as the active device.
			MySetActiveDevice(list[i]);

			MySwitchTorque(POSITION);

			wcout << "Do you need to perform the gravity calibration trajectory? (y/n)." << endl;
			wcout << "Recommended if you haven't done any yet, but please insure you have enough space: 1.5-meter clear all around the robot!" << endl;
			wcin >> ansCalib;

			// load/generate the optimal gravity parameters
			if (ansCalib=='y')
			{
				if (list[i].DeviceType==SPHERICAL_7DOF_SERVICE)
				{
					ROBOT_TYPE type = SPHERICAL_7DOF_SERVICE;
					MyRunGravityEstimationSequence7dof(type, OptimalzParam);
				}

			}
			else
			{
				(*MyMoveHome)();
				cout << "The parameters will be read from the following text file: ParametersOptimal_Kinova.txt" << endl;
				ifstream Paramfile("ParametersOptimal_Kinova.txt", ios::in);
				for (int pp=0; pp<OPTIMAL_Z_PARAM_SIZE_7DOF; pp++)
				{
					Paramfile >> OptimalzParam[pp];
				}
			}

			//display
			wcout << "The optimal gravity parameters are" << endl;
			for (int pp=0; pp<OPTIMAL_Z_PARAM_SIZE_7DOF; pp++)
			{
				wcout << OptimalzParam[pp] << endl;
			}
			wcout << endl;

			//send the optimal gravity parameters to the robot
			for (int pp=0; pp<OPTIMAL_Z_PARAM_SIZE_7DOF; pp++)
			{
				GravParamCommand[pp]=OptimalzParam[pp];
			}
			MySetGravityOptimalZParam(GravParamCommand);

			//set optimal gravity type
			MySetGravityType(OPTIMAL);

			//switch to torque mode
			MySwitchTorque(TORQUE);

			wcout << "Here you have 20 seconds to play with the robot in torque mode." << endl
					<< "Try to move it with your hand" << endl << endl;
			usleep(20000000);

			wcout << "Now, we will send a torque command to joint 6 during 5 seconds" << endl << endl;
			MySetSafetyFactorTorque(0.8);
			usleep(3000000);
			TorqueCommand[5]=-1.0f;
			for (int s=0; s<500; s++)
			{
				MySendAngularTorqueCommand(TorqueCommand);
				usleep(6000);
			}

			wcout << "Now, we will send downward force command during 5 seconds" << endl;
			usleep(3000000);
			wcout << "Please, place your hand below the hand to support it" << endl << endl;
			usleep(3000000);
			TorqueCommand[5]=0.0f; //reinitialize TorqueCommand
			TorqueCommand[2]=-3.0; //3N force command in Z-
			for (int s=0; s<500; s++)
			{
				MySendCartesianForceCommand(TorqueCommand);
				usleep(6000);
			}

			wcout << "Back to Trajectory mode" << endl << endl;
			MySwitchTorque(POSITION);

		}

		result = (*MyCloseAPI)();
	}

	dlclose(commandLayer_handle);

	return 0;
}
