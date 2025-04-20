#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    FILE *fp;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(PORT); 
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    char filename[100];
    printf("Enter filename to send: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (!fp) {
        perror("File open failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    int n;
    while ((n = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        sendto(sockfd, buffer, n, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    }

    // Send END to indicate file transmission complete
    sendto(sockfd, "END", strlen("END"), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("File sent successfully.\n");

    fclose(fp);
    close(sockfd);
    return 0;
}
