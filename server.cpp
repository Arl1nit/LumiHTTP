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
        cout << "Error" << endl;
    }
    // sockaddr_in serverAdress;
    // serverAdress.sin_family = AF_INET;
    // serverAdress.sin_port = htons(8080);
    return 0;
}
