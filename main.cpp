#include <iostream>
#include <windows.h>
#include "lib\deviceManager.h"
using namespace std;


int main(int argc, const char **argv){
    DeviceManager deviceManager("device_log.txt");
    deviceManager.labelInitialDevices();  // Label initial devices as BoardInterface
    // deviceManager.logDevices();            // Log initial devices

    
    while( true ){
        Sleep(2000);
        std::string data = deviceManager.checkNewDevices();
        if (!data.empty() || data.find("Instance(s)") != std::string::npos)
            std::cout << data << std::endl;
        
    }
    

    return 0;        
}
