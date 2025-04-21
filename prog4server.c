#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BUFFER_SIZE 2048

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256], filedata[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    FILE *fp;
    int bytes_read;

    // Check for port argument
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Setup server address structure
    memset(&serv_addr, 0, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    listen(sockfd, 5);
    printf("Server waiting for client connection...\n");

    // Accept connection
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("Accept failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Receive filename
    memset(buffer, 0, sizeof(buffer));
    if (read(newsockfd, buffer, sizeof(buffer) - 1) < 0) {
        perror("Error reading filename");
        close(newsockfd);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server received filename: %s\n", buffer);

    // Open and read file
    fp = fopen(buffer, "r");
    if (fp == NULL) {
        perror("File not found");
        write(newsockfd, "File not found!\n", 17);
    } else {
        memset(filedata, 0, sizeof(filedata));
        bytes_read = fread(filedata, 1, sizeof(filedata) - 1, fp);
        write(newsockfd, filedata, bytes_read);
        fclose(fp);
        printf("File sent to client.\n");
    }

    // Cleanup
    close(newsockfd);
    close(sockfd);
    return 0;
}
