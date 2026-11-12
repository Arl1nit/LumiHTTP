#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "fileReader.h"
#include "router.h"
#include "config.h"

using namespace std;

int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    Config LumiConf = loadConfig();

    if(LumiConf.showLogs && serverSocket < 0)
    {
        cout << "Socket creation failed!" << endl;
        return 1;
    }

    sockaddr_in serverAdress{};
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(LumiConf.port);
    serverAdress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAdress, sizeof(serverAdress));
    listen(serverSocket, LumiConf.backlog);
    while(true)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        char buffer[1024] = {};
        read(clientSocket, buffer, sizeof(buffer));
        string request = buffer;
        string accesingFilePath = routeRequest(request);

        if(LumiConf.showLogs) cout << buffer << endl;

        string body = readFile(accesingFilePath);
        string responce =
            "HTTP/1.1 200 OK\r\n"
            "Server: "+ LumiConf.serverName +"\r\n"
            "Content-Type: "+ getContentType(accesingFilePath) +"; charset=utf-8\r\n"
            "Content-Length:" + to_string(body.size()) +"\r\n"
            "Connection: close\r\n"
            "\r\n" + body;
        send(clientSocket, responce.c_str(), responce.size(), 0);
        close(clientSocket);
    }
    return 0;
}
