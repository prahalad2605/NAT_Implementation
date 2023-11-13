// Client side implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize server address struct
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "localhost", &(serverAddr.sin_addr));

    // Connect to the server
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Menu for user interaction
    printf("Menu:\n");
    printf("1. Check IP Mapping\n");
    printf("2. Add New Mapping\n");

    int option;
    printf("Enter option: ");
    scanf("%d", &option);

    send(clientSocket, &option, sizeof(int), 0);

    if (option == 1) {
        // Option 1: Check and provide corresponding global address
        char localAddress[15];
        printf("Enter local IP address: ");
        scanf("%s", localAddress);
        send(clientSocket, localAddress, sizeof(localAddress), 0);

        char buffer[1024];
        recv(clientSocket, buffer, sizeof(buffer), 0);
        printf("Response: %s\n", buffer);
    } else if (option == 2) {
        // Option 2: Add new mapping
        char localAddress[15], globalAddress[15];
        printf("Enter local IP address: ");
        scanf("%s", localAddress);
        printf("Enter global IP address: ");
        scanf("%s", globalAddress);

        send(clientSocket, localAddress, sizeof(localAddress), 0);
        send(clientSocket, globalAddress, sizeof(globalAddress), 0);

        char buffer[1024];
        recv(clientSocket, buffer, sizeof(buffer), 0);
        printf("Response: %s\n", buffer);
    }

    // Close the client socket
    close(clientSocket);

    return 0;
}