#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    FILE *fp;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(PORT); 

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is ready. Waiting for file...\n");

    fp = fopen("received_file.txt", "w");
    if (!fp) {
        perror("File open failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    int n;
    while (1) {
        n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (n <= 0 || strcmp(buffer, "END") == 0) {
            break;
        }
        fwrite(buffer, 1, n, fp);
    }

    printf("File received and saved as 'received_file.txt'.\n");

    fclose(fp);
    close(sockfd);
    return 0;
}
