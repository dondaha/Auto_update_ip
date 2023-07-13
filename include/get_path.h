#ifndef GETMYIPADDRESS_GET_PATH_H
#define GETMYIPADDRESS_GET_PATH_H
#include "filesystem"

namespace fs = std::filesystem;

static char *argv0;

void init_argv(char *argv[]);
std::string get_config_path();
std::string get_ali_update_path();
#endif //GETMYIPADDRESS_GET_PATH_H
