#ifndef DEVICEMANAGER
#define DEVICEMANAGER

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <cctype>
#include "DeviceInfo.h"

class DeviceManager {
    private:
        std::vector<DeviceInfo> devices;
        std::string logfile;

        void loadDevices();
        void saveDevices();

    public:
        DeviceManager(std::string logfile) : logfile(logfile) {
            loadDevices();
        }

        void scanDevices(std::vector<DeviceInfo>& scannedDevices);
        void labelInitialDevices();
        std::string checkNewDevices();
        void logDevices();

        bool deviceExists(const std::string& vid, const std::string& pid) const;
        std::vector<DeviceInfo> get_devices() const;
        std::string get_log_file() const;
};

inline std::string exec(const char* command){
    std::array<char, 256> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    if (!pipe) 
        throw std::runtime_error("popen() failed!");
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) 
        result += buffer.data();
    
    return result;
}

inline std::vector<std::string> split(const std::string tmp, const char c) { 
    std::vector<std::string> slicedStrings;
    size_t start = 0;
    size_t pos = tmp.find(c);

    while (pos != std::string::npos) {
        slicedStrings.push_back(tmp.substr(start, pos - start));
        start = pos + 1;
        pos = tmp.find(c, start);
    }
    slicedStrings.push_back(tmp.substr(start));

    return slicedStrings;
}

inline std::string reduceWhitespaces(const std::string& str) {
    std::string result;
    bool inWhitespace = false;

    for (char ch : str) {
        if (std::isspace(ch)) {
            if (!inWhitespace) {
                result += ' ';
                inWhitespace = true;
            }
        } else {
            result += ch;
            inWhitespace = false;
        }
    }

    if (!result.empty() && std::isspace(result.back())) {
        result.pop_back();
    }

    return result;
}

#endif