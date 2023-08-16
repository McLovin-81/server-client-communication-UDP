#include <iostream>
#include <cstring>
#include <arpa/inet.h>

int main()
{
    int serverSocket; 
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientLength = sizeof(clientAddress);
    char buffer[1024]; // Declare a character array (buffer) to store data sent and received.

    // // Create socket using IPv4 address and UDP protocol
    serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Prepare server address.
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(23232);

    // Bind the socket to the server address
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Receive data from clients
    while(true)
    {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(serverSocket, buffer, sizeof(buffer), 0,
            (struct sockaddr*)&clientAddress, &clientLength);
        
        std::cout << "Received from client " << inet_ntoa(clientAddress.sin_addr) << ": " << buffer << std::endl;

        // Echo the received data back to the client
        sendto(serverSocket, "Hello Back", strlen(buffer), 0, (struct sockaddr*)&clientAddress, clientLength);
    }
    return 0;
}