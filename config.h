#pragma once
#include <string>

using namespace std;

struct Config
{
    int port = 8080;
    string webRoot = "./web";
    string serverName = "LumiHTTP";
    bool showLogs = true;
};

Config loadConfig();
