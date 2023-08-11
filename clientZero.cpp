#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    // Prepare server address
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(23232);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
    
    char message[] = "Hello, server!";
    
    // Send data to server
    sendto(clientSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    
    // Receive data from server
    recvfrom(clientSocket, buffer, sizeof(buffer), 0, NULL, NULL);
    
    std::cout << "Received from server: " << buffer << std::endl;
    
    // Close the socket
    close(clientSocket);
    
    return 0;
}

