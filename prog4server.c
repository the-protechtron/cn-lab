#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BUFFER_SIZE 2048

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256], filedata[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    FILE *fp;
    int n;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd, 5);
    printf("Server waiting for client connection...\n");

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");

    // Receive filename
    memset(buffer, 0, sizeof(buffer));
    n = read(newsockfd, buffer, sizeof(buffer) - 1);
    if (n < 0)
        error("ERROR reading from socket");

    printf("Server received filename: %s\n", buffer);

    fp = fopen(buffer, "r");
    if (fp == NULL) {
        printf("File not found.\n");
        write(newsockfd, "File not found!\n", 17);
    } else {
        memset(filedata, 0, sizeof(filedata));
        fread(filedata, 1, sizeof(filedata) - 1, fp);
        write(newsockfd, filedata, strlen(filedata));
        fclose(fp);
        printf("File sent to client.\n");
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
