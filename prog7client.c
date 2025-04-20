// mkfifo fifo1
// mkfifo fifo2
// do them beforehand


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char buffer[1024];
    int fd1, fd2, file_fd, n;

    // Open FIFOs
    fd1 = open("fifo1", O_WRONLY);  // write to server
    fd2 = open("fifo2", O_RDONLY);  // read from server

    if (fd1 < 0 || fd2 < 0) {
        perror("FIFO open failed");
        return 1;
    }

    printf("Connected to server using FIFOs\n");

    // Read welcome message
    read(fd2, buffer, sizeof(buffer));
    printf("Server says: %s\n", buffer);

    // Send file name to server
    char filename[] = "text.txt";
    write(fd1, filename, strlen(filename) + 1);
    printf("Requested file: %s\n", filename);

    // Read file content from server
    n = read(fd2, buffer, sizeof(buffer));
    if (n <= 0) {
        printf("File not received or empty.\n");
        return 1;
    }

    buffer[n] = '\0';  // Null-terminate
    printf("Received file content:\n%s\n", buffer);

    // Save to file
    file_fd = open("recvd.txt", O_CREAT | O_WRONLY, 0644);
    write(file_fd, buffer, n);
    close(file_fd);

    // Close FIFOs
    close(fd1);
    close(fd2);

    return 0;
}
