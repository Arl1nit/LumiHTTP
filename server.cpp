#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSocket < 0)
    {
        cout << "Socket creation failed!" << endl;
        return 1;
    }

    sockaddr_in serverAdress{};
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(8080);
    serverAdress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAdress, sizeof(serverAdress));
    listen(serverSocket, 5);
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    char buffer[1024] = {};
    read(clientSocket, buffer, sizeof(buffer));

    cout << buffer << endl;

    return 0;
}
