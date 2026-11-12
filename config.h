#pragma once
#include <string>

using namespace std;

struct Config
{
    int port = 8080;
    string webRoot = "./web";
    string serverName = "LumiHTTP";
    bool showLogs = true;
    int backlog = 10;
};

Config loadConfig();
