#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    FILE *fp;
    socklen_t addr_size;
    int bytes_read, total_sent = 0;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server details
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    addr_size = sizeof(server_addr);

    // Input filename
    char filename[100];
    printf("Enter filename to send: ");
    scanf("%s", filename);

    // Open file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Send file content
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        if (sendto(sockfd, buffer, bytes_read, 0, (struct sockaddr*)&server_addr, addr_size) < 0) {
            perror("Error sending file data");
            fclose(fp);
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        total_sent += bytes_read;
    }

    // Send END message to tell server we're done
    strcpy(buffer, "END");
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, addr_size);

    printf("File sent successfully (%d bytes).\n", total_sent);

    fclose(fp);
    close(sockfd);
    return 0;
}
