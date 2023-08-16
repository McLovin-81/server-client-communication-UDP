#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    // Prepare server address
    struct sockaddr_in serverAddress; // Declare a structure to hold the server address information.
    socklen_t serverLength = sizeof(serverAddress);
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(23232);
    serverAddress.sin_addr.s_addr = inet_addr("10.127.220.39");
    
    char message[] = "Hello, server!";
    
    // Send data to server
    sendto(clientSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    
    // Receive data from server
    recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddress, &serverLength);
    
    std::cout << "Received from server " << inet_ntoa(serverAddress.sin_addr) << ": " << buffer << std::endl;
    
    // Close the socket
    close(clientSocket);
    
    return 0;
}

