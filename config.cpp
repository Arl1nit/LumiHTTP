#include "config.h"
#include <fstream>

using namespace std;

Config loadConfig()
{
    Config config;
    ifstream file("lumi.conf");
    string line;

    while(getline(file, line))
    {
        auto eql = line.find("=");
        if(eql == string::npos)
        {
            continue;
        }

        string key = line.substr(0,eql);
        string value = line.substr(eql+1);

        if (key=="port") config.port = stoi(value);
        else if (key == "web_root") config.webRoot = value;
        else if (key == "server_name") config.serverName = value;
        else if (key == "show_logs") config.showLogs = (value == "true");
    }

    return config;
}
