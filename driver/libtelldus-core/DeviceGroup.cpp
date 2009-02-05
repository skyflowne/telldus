#include <stdlib.h>

#include "DeviceGroup.h"
#include "Manager.h"

using namespace TelldusCore;

const int ALL_METHODS =
		TELLSTICK_TURNON |
		TELLSTICK_TURNOFF |
		TELLSTICK_BELL |
		TELLSTICK_DIM;

/*
* Constructor
*/
DeviceGroup::DeviceGroup(int model, const std::string &strDevices)
	:Device(model)
{
	if (strDevices.length() > 0) {
		char *tempDevices = new char[strDevices.size()+1];
#ifdef _WINDOWS
		strcpy_s(tempDevices, strDevices.size()+1, strDevices.c_str());
#else
		strcpy(tempDevices, strDevices.c_str());
#endif

		Manager *manager = Manager::getInstance();
		char *strToken = strtok(tempDevices, ",");
		do {
			int intDevice = atoi(strToken);
			Device *device = manager->getDevice(intDevice);
			if (device != NULL) {
				deviceList.push_back( device );
			}
		} while ( (strToken = strtok(NULL, ",")) != NULL );

		free(tempDevices);
	}
}

/*
* Destructor
*/
DeviceGroup::~DeviceGroup(void) {
}

/*
* Turn on this device
*/
int DeviceGroup::turnOn(void) {
	int retVal = TELLSTICK_ERROR_UNKNOWN;
	
	for (DeviceList::const_iterator it = deviceList.begin(); it != deviceList.end(); ++it) {
		int methods = (*it)->methods(ALL_METHODS);
		if (ALL_METHODS & TELLSTICK_TURNON) {
			int success = (*it)->turnOn();
			if (retVal != TELLSTICK_SUCCESS) {
				retVal = success;
			}
		}
	}
	return retVal;
}

/*
* Turn off this device
*/
int DeviceGroup::turnOff(void) {
	int retVal = TELLSTICK_ERROR_UNKNOWN;
	
	for (DeviceList::const_iterator it = deviceList.begin(); it != deviceList.end(); ++it) {
		int methods = (*it)->methods(ALL_METHODS);
		if (ALL_METHODS & TELLSTICK_TURNOFF) {
			int success = (*it)->turnOff();
			if (retVal != TELLSTICK_SUCCESS) {
				retVal = success;
			}
		}
	}
	return retVal;
}

/*
* Send a bell
*/
int DeviceGroup::bell(void){
	int retVal = TELLSTICK_ERROR_UNKNOWN;
	
	for (DeviceList::const_iterator it = deviceList.begin(); it != deviceList.end(); ++it) {
		int methods = (*it)->methods(ALL_METHODS);
		if (ALL_METHODS & TELLSTICK_BELL) {
			int success = (*it)->bell();
			if (retVal != TELLSTICK_SUCCESS) {
				retVal = success;
			}
		}
	}
	return retVal;
}

/*
* Turn off this device
*/
int DeviceGroup::dim(unsigned char level){
	int retVal = TELLSTICK_ERROR_UNKNOWN;
	
	for (DeviceList::const_iterator it = deviceList.begin(); it != deviceList.end(); ++it) {
		int methods = (*it)->methods(ALL_METHODS);
		if (ALL_METHODS & TELLSTICK_DIM) {
			int success = (*it)->dim(level);
			if (retVal != TELLSTICK_SUCCESS) {
				retVal = success;
			}
		}
	}
	return retVal;
}

/*
* Has the device got the method?
*/
int DeviceGroup::methods(int supportedMethods){
	int retVal = 0;
	
	for (DeviceList::const_iterator it = deviceList.begin(); it != deviceList.end(); ++it) {
		retVal = retVal | (*it)->methods(supportedMethods);
	}
	
	return retVal;
}

std::string DeviceGroup::getProtocol() const {
	return "group";
}