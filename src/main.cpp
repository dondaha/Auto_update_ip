#include <cstdio>
#include <chrono>
#include <thread>
#include "CheckIP.h"
#include "windows.h"
#include "get_path.h"

namespace fs = std::filesystem;


void update(){
    CheckIP checkIP;
    checkIP.update_ip();
}


int main(int argc, char *argv[]) {
    init_argv(argv);
//    HWND hWnd = GetConsoleWindow(); // 为啥这个不行啊
    HWND hWnd = GetForegroundWindow();
    CheckIP checkIP;
    if (checkIP.is_first_launch()){
        printf("First launch, created config.yaml, please edit it.\n");
        system("pause");
        return 0;
    }
    checkIP.~CheckIP();
    auto config = YAML::LoadFile(get_config_path());
    int interval = config["Update_info"]["update_interval"].as<int>();
    bool hide_windows = config["Update_info"]["hide_windows"].as<bool>();
    // 隐藏窗口
    if (hide_windows) ShowWindow(hWnd, SW_HIDE);
    while (true){
        update();
        printf("Wait for %d seconds\n---------------\n", interval);
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}
