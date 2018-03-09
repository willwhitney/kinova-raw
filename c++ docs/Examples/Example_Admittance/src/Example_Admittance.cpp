#include <iostream>
#include <dlfcn.h>
#include <vector>
#include "../../../API/USBCommLayerUbuntu/Projects/Eclipse/Kinova.API.CommLayerUbuntu.h"
#include "../../../API/USBCommandLayerUbuntu/Projects/Eclipse/Kinova.API.UsbCommandLayerUbuntu.h"
#include "../../../API/USBCommandLayerUbuntu/Projects/Eclipse/KinovaTypes.h"
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
	int (*MyStartForceControl)();
	int (*MyGetDevices)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result);
	int (*MySetActiveDevice)(KinovaDevice device);

	//We load the library
	commandLayer_handle = dlopen("Kinova.API.USBCommandLayerUbuntu.so",RTLD_NOW|RTLD_GLOBAL);

	//We load the functions from the library
	MyInitAPI = (int (*)()) dlsym(commandLayer_handle,"InitAPI");
	MyCloseAPI = (int (*)()) dlsym(commandLayer_handle,"CloseAPI");
	MyStartForceControl = (int (*)()) dlsym(commandLayer_handle,"StartForceControl");
	MyGetDevices = (int (*)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result)) dlsym(commandLayer_handle,"GetDevices");
	MySetActiveDevice = (int (*)(KinovaDevice devices)) dlsym(commandLayer_handle,"SetActiveDevice");


	//If the was loaded correctly
	if((MyInitAPI == NULL) || (MyCloseAPI == NULL) || (MyGetDevices == NULL)
	|| (MySetActiveDevice == NULL) || (MyStartForceControl == NULL))
	{
		cout << "* * *  E R R O R   D U R I N G   I N I T I A L I Z A T I O N  * * *" << endl;
	}
	else
	{
		cout << "I N I T I A L I Z A T I O N   C O M P L E T E D" << endl << endl;

		result = (*MyInitAPI)();

		cout << "Initialization's result :" << result << endl;

		KinovaDevice list[MAX_KINOVA_DEVICE];

		int devicesCount = MyGetDevices(list, result);

		for(int i = 0; i < devicesCount; i++)
		{
			cout << "Found a robot on the USB bus (" << list[i].SerialNumber << ")" << endl;

			//Setting the current device as the active device.
			MySetActiveDevice(list[i]);

			MyStartForceControl();
		}

		result = (*MyCloseAPI)();
	}

	dlclose(commandLayer_handle);

	return 0;
}
