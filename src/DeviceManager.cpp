#include "..\lib\DeviceManager.h"

std::string deviceListCommand = "wmic path Win32_PnPEntity where \"DeviceID like 'USB%'\" get DeviceID";
std::string deviceInformationCommand = "wmic path Win32_PnPEntity where \"DeviceID like '%RECORDID%'\" get name, DeviceID";
size_t pos = deviceInformationCommand.find("RECORDID");


void DeviceManager::loadDevices(){
    std::ifstream file(logfile);
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        devices.push_back(DeviceInfo::from_string(line));
    }

    for (auto device : devices)
        std::cout << device.to_string() << std::endl;
    

    file.close();   
}

void DeviceManager::saveDevices(){
    std::ofstream file(get_log_file());
    for (const auto& device : devices) {
        file << device.to_string() << "\n";
    }
    file.close();
}

void DeviceManager::scanDevices(std::vector<DeviceInfo>& scannedDevices) {
    std::string pid, vid, name, device_id;

    // extract list of all devices connected to motherboard
    std::string deviceList = exec(deviceListCommand.c_str());
    for (auto device: split(deviceList, '\n')){ 
        // parse and extract VID&PID
        std::vector<std::string> deviceInformation = split(device, '\\');

        if (deviceInformation.size() != 3) // check for correct data
            continue;

        std::string command = deviceInformationCommand;
        command = command.replace(pos, 8, deviceInformation.at(1));
        // replace VID&PID and get DeviceID and name
        std::string recordInfo = exec(command.c_str());

        std::vector<std::string> lines = split(recordInfo, '\n');
        for (const auto& line : lines) {
            // Skip empty lines and the header line
            if (line.empty() || line.find("DeviceID") != std::string::npos) 
                continue;
            

            std::vector<std::string> attributes = split(reduceWhitespaces(line), ' ');
            if (attributes.size() < 2) {
                continue;
            }

            device_id = attributes[0];
            name.clear();
            for (int index=1; index<attributes.size(); index++)
                name += attributes.at(index) + " ";
            
            size_t vidStart = command.find("VID_");
            size_t pidStart = command.find("PID_");
            if (vidStart != std::string::npos && pidStart != std::string::npos) {
                vid = command.substr(vidStart, 8); // Assuming VID_XXXX format
                pid = command.substr(pidStart, 8); // Assuming PID_XXXX format

                auto it = std::find_if(scannedDevices.begin(), scannedDevices.end(), [&pid, &vid](const DeviceInfo& d) {
                    return d.get_pid() == pid && d.get_vid() == vid;
                });

                if (it != scannedDevices.end()) {
                    it->add_name(name);
                } else {
                    scannedDevices.push_back(DeviceInfo(pid, vid, name, device_id, ""));
                }
            }
        }
    } 
}

void DeviceManager::labelInitialDevices() {
    std::vector<DeviceInfo> scannedDevices;
    scanDevices(scannedDevices);
    for (const auto& device : scannedDevices) {
        DeviceInfo labeledDevice = device;
        labeledDevice.set_label("BoardInterface");
        devices.push_back(labeledDevice);
    }
    saveDevices();
}

std::string DeviceManager::checkNewDevices(){
    std::vector<DeviceInfo> scannedDevices;
    scanDevices(scannedDevices);

    std::ostringstream newDevicesStream;

    for (const auto& device : scannedDevices) {
        auto it = std::find_if(devices.begin(), devices.end(), [&device](const DeviceInfo& d) {
            return d.get_device_id() == device.get_device_id();
        });

        if (it == devices.end()) {
            DeviceInfo newDevice = device;
            newDevice.set_label("NewDevice");
            // devices.push_back(newDevice);
            // saveDevices();
            newDevicesStream << newDevice.get_pid() << "," << newDevice.get_vid() ;
        } else {
            for (const auto& name : device.get_names()) {
                it->add_name(name);
            }
        }
    }

    return newDevicesStream.str();
}

bool DeviceManager::deviceExists(const std::string& vid, const std::string& pid) const {
    return std::any_of(devices.begin(), devices.end(), [&vid, &pid](const DeviceInfo& device) {
        return device.get_vid() == vid && device.get_pid() == pid;
    });
}


void DeviceManager::logDevices(){
   saveDevices();
   std::cout << "All devices logged successfully." << std::endl; 
}

std::string DeviceManager::get_log_file() const {
    return logfile;
}

std::vector<DeviceInfo> DeviceManager::get_devices() const {
    return devices;
}

