#include <iostream>
#include <cstring>
#include <arpa/inet.h>

int main()
{
    // Create a socket.
    int serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Prepare server address.
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(23232);

    // Bind the socket to the server address
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    char buffer[1024];
    struct sockaddr_in clientAddress;
    socklen_t clientLength = sizeof(clientAddress);

    // Receive data from clients
    while(true)
    {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(serverSocket, buffer, sizeof(buffer), 0,
            (struct sockaddr*)&clientAddress, &clientLength);
        
        std::cout << "Received from " << inet_ntoa(clientAddress.sin_addr) << ": " << buffer << std::endl;

        // Echo the received data back to the client
        sendto(serverSocket, "Hello Back", strlen(buffer), 0, (struct sockaddr*)&clientAddress, clientLength);
    }

    return 0;
}