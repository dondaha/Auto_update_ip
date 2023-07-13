#include "get_path.h"

std::string get_config_path(){
    fs::path exe_path = fs::absolute(fs::path(argv0));
    fs::path current_path = exe_path.parent_path();
    // 拼接配置文件的绝对路径
    fs::path config_path = current_path / "config.yaml";
    return config_path.string();
}


std::string get_ali_update_path(){
    fs::path exe_path = fs::absolute(fs::path(argv0));
    fs::path current_path = exe_path.parent_path();
    // 拼接阿里云更新程序的绝对路径
    fs::path ali_update_path = current_path / "ali_update.exe";
    return ali_update_path.string();
}

void init_argv(char *argv[]){
    argv0 = argv[0];
}