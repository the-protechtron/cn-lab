#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX_BUFFER 1024

void resolve_hostname(const char *hostname, char *ip_addr) {
    struct addrinfo hints, *res;
    int status;

    // Clear memory
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;        // Use IPv4
    hints.ai_socktype = SOCK_STREAM;  // TCP stream sockets

    // Get address info
    if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
        fprintf(stderr, "Error: %s\n", gai_strerror(status));
        return;
    }

    // Convert the IP to a string
    struct sockaddr_in *ipv4 = (struct sockaddr_in *) res->ai_addr;
    inet_ntop(AF_INET, &(ipv4->sin_addr), ip_addr, INET_ADDRSTRLEN);

    freeaddrinfo(res);  // Free the linked list
}

int main() {
    char hostname[MAX_BUFFER];
    char ip_address[INET_ADDRSTRLEN];

    printf("Enter Hostname: ");
    fgets(hostname, sizeof(hostname), stdin);

    // Remove newline from fgets
    hostname[strcspn(hostname, "\n")] = '\0';

    printf("\nResolving '%s'...\n", hostname);
    resolve_hostname(hostname, ip_address);
    printf("Resolved IP address: %s\n", ip_address);

    return 0;
}
