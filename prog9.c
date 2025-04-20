#include <stdio.h>

int main() {
    int bucketSize, outputRate, packetsLeft, incoming, stored = 0, time = 0;

    printf("Enter bucket size: ");
    scanf("%d", &bucketSize);

    printf("Enter output rate: ");
    scanf("%d", &outputRate);

    printf("Enter number of packets: ");
    scanf("%d", &packetsLeft);

    while (packetsLeft > 0 || stored > 0) {
        if (packetsLeft > 0) {
            printf("\nEnter size of incoming packet: ");
            scanf("%d", &incoming);
            packetsLeft--;

            if (incoming > bucketSize) {
                printf("Packet rejected: size greater than bucket capacity.\n");
                continue;
            }

            if (stored + incoming > bucketSize) {
                printf("Packet rejected: bucket overflow.\n");
                continue;
            }

            stored += incoming;
        }

        time++;
        printf("\n--- Time %d ---\n", time);

        int sent = (stored < outputRate) ? stored : outputRate;
        printf("Packet of size %d sent.\n", sent);
        stored -= sent;
        printf("Remaining in bucket: %d\n", stored);
    }

    return 0;
}
