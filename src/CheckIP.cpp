#include "CheckIP.h"


CheckIP::CheckIP() {
    if (!file_exists(get_config_path())){
        create_config();
        is_config_edit = false;
    }else{
        config = YAML::LoadFile(get_config_path());
        ip_config = config["Network_info"]["ip"].as<std::string>();
        mac_config = config["Network_info"]["mac"].as<std::string>();
        is_config_edit = true;
    }
}

CheckIP::~CheckIP() = default;

void CheckIP::create_config() {
    // 设置节点的内容
    config["Access_key"]["access_key_id"] = "access_key_id";
    config["Access_key"]["access_key_secret"] = "access_key_secret";
    config["Domain_info"]["record_id"] = 1145141919810;
    config["Domain_info"]["rr"] = "domain_prefix";
    config["Domain_info"]["type"] = "A";
    config["Network_info"]["ip"] = "192.168.1.101";
    config["Network_info"]["mac"] = "04-7B-16-1A-3A-5D";
    config["Update_info"]["interval"] = 300; // 单位为秒
    config["Update_info"]["hide_windows"] = false;
    // 创建一个yaml发射器
    YAML::Emitter out;
    // 将节点输出到发射器
    out << config;
    // 将发射器的内容输出到文件
    std::ofstream fout(get_config_path());
    fout << out.c_str();
    fout.close();
}

void CheckIP::update_ip() {
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    int card_num = 0;
    bool found = false;
    auto pIpAdapterInfo = (PIP_ADAPTER_INFO)malloc(sizeof(IP_ADAPTER_INFO));
    auto nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    if (ERROR_BUFFER_OVERFLOW == nRel){
        free(pIpAdapterInfo);
        pIpAdapterInfo = (PIP_ADAPTER_INFO)malloc(stSize);
        nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    }
    if (ERROR_SUCCESS == nRel){
        while (pIpAdapterInfo){
            char mac[18] = ""; // 声明一个空字符串，长度为18，因为mac地址有17个字符
            char ip[16] = ""; // 声明一个空字符串，长度为16，因为ip地址有15个字符
            sprintf(ip, "%s", pIpAdapterInfo->IpAddressList.IpAddress.String); // 把ip地址转换成字符串
            for (UINT i = 0; i < pIpAdapterInfo->AddressLength; i++) {
                if (i == (pIpAdapterInfo->AddressLength - 1)) {
                    sprintf(mac + i * 3, "%.2X", (int) pIpAdapterInfo->Address[i]); // 把最后一个字节追加到字符串里，不需要加"-"
                }
                else {
                    sprintf(mac + i * 3, "%.2X-", (int) pIpAdapterInfo->Address[i]); // 把每个字节追加到字符串里，需要加"-"
                }
            }
            printf("IP Address: %s\n", ip);
            printf("MAC: %s\n", mac);
            if (std::strcmp(mac, mac_config.c_str()) == 0) {
                printf("Found the right network card\n");
                found = true;
                if (std::strcmp(ip, ip_config.c_str()) == 0) {
                    printf("IP address is the same as before, nothing to do\n");
                }else{
                    printf("IP address is different from before, update it\n");
                    config["Network_info"]["ip"] = ip;
                    YAML::Emitter out;
                    out << config;
                    std::ofstream fout(get_config_path());
                    fout << out.c_str();
                    fout.close();
                    printf("updating...\n");
                    std::cout<<"Command: "<<get_ali_update_path()+std::string(" --ip ")+std::string(ip)<<"\n";
                    system((get_ali_update_path()+std::string(" --ip ")+std::string(ip)).c_str());
                    printf("update success\n");
                }
            }
            pIpAdapterInfo = pIpAdapterInfo->Next;
            ++card_num;
        }
    }
    if (pIpAdapterInfo) {
        free(pIpAdapterInfo);
    }
    if (!found)
    printf("Can't find the right network card, please check your mac address in config.yaml\n");
}

bool CheckIP::is_first_launch() const {
    return !is_config_edit;
}
