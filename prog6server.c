#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    int addrlen = sizeof(address);
    int frame_num;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Server is waiting for connection...\n");
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    printf("Client connected!\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recv(new_socket, buffer, sizeof(buffer), 0);

        if (strcmp(buffer, "exit") == 0) break;

        sscanf(buffer, "Frame %d", &frame_num);
        printf("Received: %s\n", buffer);

        // Send ACK
        send(new_socket, &frame_num, sizeof(frame_num), 0);
    }

    close(new_socket);
    close(server_fd);
    printf("Connection closed.\n");
    return 0;
}
