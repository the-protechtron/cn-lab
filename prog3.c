#include <stdio.h>

#define MAX 10
#define INFINITY 99

struct RoutingTable {
    int distance[MAX];
    int nextHop[MAX];
} table[MAX];

int cost[MAX][MAX]; // Cost matrix
int n;              // Number of routers

void distanceVectorRouting() {
    int i, j, k, updated;

    // Initialize distance and nextHop for each router
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            table[i].distance[j] = cost[i][j];
            table[i].nextHop[j] = j;
        }
    }

    // Update tables until no change
    do {
        updated = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                for (k = 0; k < n; k++) {
                    if (table[i].distance[j] > cost[i][k] + table[k].distance[j]) {
                        table[i].distance[j] = cost[i][k] + table[k].distance[j];
                        table[i].nextHop[j] = k;
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);
}

int main() {
    int i, j;

    printf("Enter the number of routers: ");
    scanf("%d", &n);

    printf("\nEnter the cost matrix (99 for infinity):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    distanceVectorRouting();

    // Display routing table
    for (i = 0; i < n; i++) {
        printf("\nRouting table for Router %c:\n", i + 'A');
        printf("Destination\tNext Hop\tCost\n");
        for (j = 0; j < n; j++) {
            if (table[i].distance[j] == INFINITY)
                printf("    %c\t\t  -\t\tinfinite\n", j + 'A');
            else
                printf("    %c\t\t  %c\t\t  %d\n", j + 'A', table[i].nextHop[j] + 'A', table[i].distance[j]);
        }
    }

    return 0;
}
