/ Server side implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

// Define a structure to represent the mapping
typedef struct {
    char localAddress[15];  // Assuming IPv4 addresses (xxx.xxx.xxx.xxx)
    char globalAddress[15];
} Mapping;

// Function to check if the given address is valid
int isValidAddress(const char *address) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, address, &(sa.sin_addr)) != 0;
}

// Function to handle client requests
void handleRequest(int clientSocket, Mapping mappings[], int *numMappings) {
    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);

    int option = atoi(buffer);

    if (option == 1) {
        // Option 1: Check and provide corresponding global address
        char localAddress[15];
        recv(clientSocket, localAddress, sizeof(localAddress), 0);

        if (isValidAddress(localAddress)) {
            int i;
            for (i = 0; i < *numMappings; i++) {
                if (strcmp(mappings[i].localAddress, localAddress) == 0) {
                    send(clientSocket, mappings[i].globalAddress, sizeof(mappings[i].globalAddress), 0);
                    break;
                }
            }

            if (i == *numMappings) {
                send(clientSocket, "Address not found", sizeof("Address not found"), 0);
            }
        } else {
            send(clientSocket, "Invalid address format", sizeof("Invalid address format"), 0);
        }
    } else if (option == 2) {
        // Option 2: Add new mapping
        Mapping newMapping;
        recv(clientSocket, newMapping.localAddress, sizeof(newMapping.localAddress), 0);
        recv(clientSocket, newMapping.globalAddress, sizeof(newMapping.globalAddress), 0);

        if (isValidAddress(newMapping.localAddress) && isValidAddress(newMapping.globalAddress)) {
            mappings[*numMappings] = newMapping;
            (*numMappings)++;
            send(clientSocket, "Mapping added successfully", sizeof("Mapping added successfully"), 0);
        } else {
            send(clientSocket, "Invalid address format", sizeof("Invalid address format"), 0);
        }
    }
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);

    // Define some initial mappings (you can add more)
    Mapping mappings[10];
    int numMappings = 0;

    strcpy(mappings[0].localAddress, "192.168.1.2");
    strcpy(mappings[0].globalAddress, "203.0.113.1");

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize server address struct
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified port
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Listen for incoming connections
    listen(serverSocket, 5);

    printf("Server listening on port 8080...\n");

    while (1) {
        // Accept a connection from the client
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);

        // Handle the client request
        handleRequest(clientSocket, mappings, &numMappings);

        // Close the client socket
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}