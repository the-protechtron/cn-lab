// make sure text.txt exists in the same folder

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    char buffer[1024];
    int fd, fd1, fd2, n;

    // Create FIFOs (named pipes) if they don't exist
    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    // Open FIFOs
    fd1 = open("fifo1", O_RDONLY); // Read from client
    fd2 = open("fifo2", O_WRONLY); // Write to client

    if (fd1 < 0 || fd2 < 0) {
        perror("Error opening FIFOs");
        exit(1);
    }

    printf("Connected to client via FIFOs\n");

    // Send welcome message
    write(fd2, "Hello from server!", 20);

    // Receive file name
    read(fd1, buffer, sizeof(buffer));
    printf("Client requested file: %s\n", buffer);

    // Try to open the requested file
    fd = open(buffer, O_RDONLY);
    if (fd < 0) {
        printf("File not found: %s\n", buffer);
        write(fd2, "ERROR: File not found", 23);
    } else {
        // Read file contents
        n = read(fd, buffer, sizeof(buffer));
        buffer[n] = '\0';  // Null terminate to print properly
        printf("Sending file content to client...\n");

        // Send to client
        write(fd2, buffer, n);
        close(fd);
    }

    close(fd1);
    close(fd2);

    return 0;
}
