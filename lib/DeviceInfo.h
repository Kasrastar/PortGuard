#ifndef DEVICEINFO
#define DEVICEINFO

#include <iostream>
#include <sstream>
#include <string>

class DeviceInfo{
    
    private:
        std::string PID;
        std::string VID;
        std::string NAME;
        std::string DEVICEID;
        std::string LABEL;

    public:

        DeviceInfo(std::string pid, std::string vid, std::string name, std::string device_id, std::string label)
        : PID(pid), VID(vid), NAME(name), DEVICEID(device_id), LABEL(label) {}

        std::string to_string() const ;
        static DeviceInfo from_string(const std::string&);

        void set_pid(std::string);
        void set_vid(std::string);
        void set_name(std::string);
        void set_device_id(std::string);
        void set_label(std::string);
        
        std::string get_pid() const;
        std::string get_vid() const;
        std::string get_name() const;
        std::string get_device_id() const;
        std::string get_label() const;

};

#endif