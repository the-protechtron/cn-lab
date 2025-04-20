#include <stdio.h>
#include <string.h>

char data[100], concatdata[117], src_crc[17], dest_crc[17], frame[120];
char divisor[18] = "10001000000100001"; // CRC-16-IBM polynomial (17 bits)
char rem[17]; // renamed from 'remainder'

void crc_cal(char *input, char *crc) {
    char temp[120];
    strcpy(temp, input);
    int len = strlen(input);

    for (int i = 0; i <= len - 17; i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < 17; j++) {
                temp[i + j] = (temp[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    strncpy(crc, &temp[len - 16], 16);
    crc[16] = '\0';
}

int main() {
    printf("\n\t\t\tAT SOURCE NODE\n\nEnter the binary data to send: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0'; // Remove newline

    // Append 16 zeros (since CRC-16)
    strcpy(concatdata, data);
    strcat(concatdata, "0000000000000000");

    // Calculate CRC
    crc_cal(concatdata, src_crc);

    // Display the frame
    printf("\nData: %s", data);
    printf("\nCRC: %s", src_crc);
    printf("\nTransmitted Frame: %s%s", data, src_crc);

    printf("\n\n\t\tSOURCE NODE TRANSMITTED THE FRAME ---->\n");

    printf("\n\n\t\t\tAT DESTINATION NODE\nEnter the received frame: ");
    fgets(frame, sizeof(frame), stdin);
    frame[strcspn(frame, "\n")] = '\0';

    crc_cal(frame, dest_crc);

    if (strcmp(dest_crc, "0000000000000000") == 0) {
        printf("\nReceived frame is ERROR-FREE \n");
    } else {
        printf("\nReceived frame has ERRORS \n");
    }

    return 0;
}
