#include <iostream>
#include <memory>
#include <vector>
#include <array>

using namespace std;

std::string exec(const char* command){
    std::array<char, 256> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    if (!pipe) 
        throw std::runtime_error("popen() failed!");
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) 
        result += buffer.data();
    
    return result;
}

int main(){
    vector<std::string> commands = {
        "g++ -c .\\src\\DeviceInfo.cpp",
        "g++ -c .\\src\\DeviceManager.cpp",
        "g++ -c main.cpp",
        "g++ *.o -o test",
        "del *.o"
    };
    for(auto cmd: commands)
        cout << exec(cmd.c_str());
}
