#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BUFFER_SIZE 2048

int main(int argc, char *argv[]) {
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char filename[256], buffer[BUFFER_SIZE];
    int bytes_received;

    // Check for correct usage
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Extract port number
    portno = atoi(argv[2]);

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Resolve server address
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR: No such host\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Setup server address structure
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Input filename to request
    printf("Enter filename to request from server: ");
    scanf("%s", filename);

    // Send filename to server
    if (write(sockfd, filename, strlen(filename)) < 0) {
        perror("Error sending filename");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Receive file content from server
    memset(buffer, 0, sizeof(buffer));
    bytes_received = read(sockfd, buffer, sizeof(buffer) - 1);
    if (bytes_received < 0) {
        perror("Error reading from socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Output received content
    printf("\nReceived content from server:\n");
    printf("%s\n", buffer);

    // Cleanup
    close(sockfd);
    return 0;
}
