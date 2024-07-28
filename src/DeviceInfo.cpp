#include "..\lib\DeviceInfo.h"

// Implementation of member functions
std::string DeviceInfo::to_string() const {
    std::ostringstream oss;
    oss << PID << "," << VID << ",";
    for (const auto& name : NAMES) {
        oss << name << ";";
    }
    oss << "," << DEVICEID << "," << LABEL;
    return oss.str();
}

DeviceInfo DeviceInfo::from_string(const std::string& str) {
    std::istringstream iss(str);
    std::string pid, vid, device_id, label, names_str;
    getline(iss, pid, ',');
    getline(iss, vid, ',');
    getline(iss, names_str, ',');
    getline(iss, device_id, ',');
    getline(iss, label, ',');

    std::unordered_set<std::string> names;
    std::istringstream names_stream(names_str);
    std::string name;
    while (getline(names_stream, name, ';')) {
        if (!name.empty()) {
            names.insert(name);
        }
    }

    DeviceInfo device(pid, vid, "", device_id, label);
    device.NAMES = names;
    return device;
}

void DeviceInfo::set_pid(std::string pid) {
    PID = pid;
}

void DeviceInfo::set_vid(std::string vid) {
    VID = vid;
}

void DeviceInfo::add_name(std::string name) {
    NAMES.insert(name);
}

void DeviceInfo::set_device_id(std::string device_id) {
    DEVICEID = device_id;
}

void DeviceInfo::set_label(std::string label) {
    LABEL = label;
}

std::string DeviceInfo::get_pid() const {
    return PID;
}

std::string DeviceInfo::get_vid() const {
    return VID;
}

std::unordered_set<std::string> DeviceInfo::get_names() const {
    return NAMES;
}

std::string DeviceInfo::get_device_id() const {
    return DEVICEID;
}

std::string DeviceInfo::get_label() const {
    return LABEL;
}

bool DeviceInfo::operator==(const DeviceInfo& other) const {
    return PID == other.PID && VID == other.VID;
}
