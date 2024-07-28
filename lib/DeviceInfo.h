#ifndef DEVICEINFO
#define DEVICEINFO

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

class DeviceInfo{
    
    private:
        std::string PID;
        std::string VID;
        std::unordered_set<std::string> NAMES;
        std::string DEVICEID;
        std::string LABEL;

    public:
        DeviceInfo(std::string pid, std::string vid, std::string name, std::string device_id, std::string label)
        : PID(pid), VID(vid), DEVICEID(device_id), LABEL(label) {
            NAMES.insert(name);
        }

        std::string to_string() const;
        static DeviceInfo from_string(const std::string&);

        void set_pid(std::string);
        void set_vid(std::string);
        void add_name(std::string);
        void set_device_id(std::string);
        void set_label(std::string);

        std::string get_pid() const;
        std::string get_vid() const;
        std::unordered_set<std::string> get_names() const;
        std::string get_device_id() const;
        std::string get_label() const;

        bool operator==(const DeviceInfo&) const;
};

#endif
