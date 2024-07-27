#include "..\lib\DeviceInfo.h"

std::string DeviceInfo::to_string() const {
        std::stringstream ss;
        ss << PID << "|" << VID << "|" << NAME << "|" << DEVICEID << "|" << LABEL;
        return ss.str();
    }

DeviceInfo DeviceInfo::from_string(const std::string& str) {
    std::stringstream ss(str);
    std::string pid, vid, name, device_id, label;

    std::getline(ss, pid, '|');
    std::getline(ss, vid, '|');
    std::getline(ss, name, '|');
    std::getline(ss, device_id, '|');
    std::getline(ss, label, '|');

    return DeviceInfo(pid, vid, name, device_id, label);
}

void DeviceInfo::set_pid(std::string value){
    PID = value;
}

void DeviceInfo::set_vid(std::string value){
    VID = value;
}

void DeviceInfo::set_name(std::string value){
    NAME = value;
}

void DeviceInfo::set_device_id(std::string value){
    DEVICEID = value;
}

void DeviceInfo::set_label(std::string value){
    LABEL = value;
}

std::string DeviceInfo::get_pid() const {
    return PID;
}

std::string DeviceInfo::get_vid() const {
    return VID;
}
std::string DeviceInfo::get_name() const {
    return NAME;
}
std::string DeviceInfo::get_device_id() const {
    return DEVICEID;
}
std::string DeviceInfo::get_label() const {
    return LABEL;
}