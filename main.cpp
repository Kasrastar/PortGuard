#include <iostream>
#include <windows.h>
#include "lib\deviceManager.h"
using namespace std;


int main(int argc, const char **argv){
    DeviceManager deviceManager("device_log.txt");
    // deviceManager.labelInitialDevices();  // Label initial devices as BoardInterface
    // deviceManager.logDevices();            // Log initial devices

    
    // while( 1 ){
    //     Sleep(2000);
    //     // To check for new devices
    //     deviceManager.checkNewDevices();
        
    // }
    

    return 0;        
}
