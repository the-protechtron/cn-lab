#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_FRAMES 10
#define WINDOW_SIZE 4
#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    int base = 0, next_frame = 0, ack;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0);

    printf("Connected to server!\n");

    while (base < MAX_FRAMES) {
        while (next_frame < base + WINDOW_SIZE && next_frame < MAX_FRAMES) {
            sprintf(buffer, "Frame %d", next_frame);
            send(sockfd, buffer, strlen(buffer) + 1, 0);
            printf("📤 Sent: %s\n", buffer);
            next_frame++;
        }

        recv(sockfd, &ack, sizeof(ack), 0);
        printf("Received ACK for Frame %d\n", ack);
        base = ack + 1;
    }

    // Send exit to stop server loop
    send(sockfd, "exit", strlen("exit") + 1, 0);

    close(sockfd);
    printf("All frames sent successfully!\n");
    return 0;
}
