#include <stdio.h>
#include <WinSock.h>
#include <IPHlpApi.h>
#include "file_exists.h"
#include "iostream"
#include <fstream>
#include "yaml-cpp/yaml.h"
#include "filesystem"
#include "get_path.h"

namespace fs = std::filesystem;

#pragma comment(lib, "Iphlpapi.lib")

class CheckIP {
private:
    YAML::Node config;
    std::string ip_config;
    std::string mac_config;
    bool is_config_edit; // 默认配置文件是否修改
public:
    CheckIP();
    ~CheckIP();
    void create_config();
    bool is_first_launch() const;
    void update_ip();
};