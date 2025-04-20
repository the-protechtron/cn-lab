#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  int b[50];
  int maxp = 6;
  int a[50], temp[70], temp2[70];
  int t, i, j, k, nd, n, m, nh, sum = 0, pos = 0;

  printf("Enter Length of Data String: ");
  scanf("%d", & nd);

  printf("Enter Data String (space-separated bits): ");
  for (i = 0; i < nd; i++) {
    scanf("%d", & a[i]);
  }

  printf("\n-----------------------------------\n");

  // Insert parity bits (initially 0)
  for (i = 0, j = 0; i < nd; i++) {
    for (k = 0; k < maxp; k++) {
      t = pow(2, k) - 1;
      if (j == t) {
        temp[j] = 0; // parity placeholder
        j++;
      }
    }
    temp[j] = a[i];
    j++;
  }

  nh = j;
  n = nh - nd;
  printf("Length of Hamming code: %d bits\n", nh);
  printf("Number of Parity Bits: %d \n", n);

  // Calculate parity bits
  m = n - 1;
  for (k = 0; k < n; k++) {
    t = pow(2, k) - 1;

    for (i = t; i < nh;) {
      for (j = 0; j <= t; j++) {
        sum += temp[i];
        i++;
        if (i >= nh)
          break;
      }

      if (i >= nh)
        break;

      for (j = 0; j <= t; j++) {
        i++;
        if (i >= nh)
          break;
      }
    }
    temp[t] = sum % 2;
    sum = 0;
    printf("P%d: %d\n", t + 1, temp[t]);
  }

  printf("\nHamming code: Sender side (transmit this): ");
  for (i = 0; i < nh; i++) {
    printf("%d ", temp[i]);
  }

  // Receiver side input
  printf("\n\nEnter received Hamming code (%d bits):\n", nh);
  for (i = 0; i < nh; i++) {
    scanf("%d", & temp2[i]);
  }

  // Error detection
  sum = 0;
  m = n - 1;
  for (k = 0; k < n; k++) {
    t = pow(2, k) - 1;

    for (i = t; i < nh;) {
      for (j = 0; j <= t; j++) {
        sum += temp2[i];
        i++;
        if (i >= nh)
          break;
      }

      if (i >= nh)
        break;

      for (j = 0; j <= t; j++) {
        i++;
        if (i >= nh)
          break;
      }
    }
    b[m] = sum % 2;
    sum = 0;
    printf("P%d: %d\n", t + 1, b[m]);
    m--;
  }

  for (m = 0; m < n; m++) {
    pos += b[n - m - 1] * pow(2, m);
  }

  printf("Position of Error: %d\n", pos);

  if (pos != 0) {
    temp2[pos - 1] = (temp2[pos - 1] == 0) ? 1 : 0;
  }

  printf("\nHamming code: Receiver side: Error Corrected: ");
  for (i = 0; i < nh; i++) {
    printf("%d ", temp2[i]);
  }

  printf("\n-----------------------------------\n");
  return 0;
}